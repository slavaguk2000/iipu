using System;
using System.Collections.Generic;
using System.Drawing;
using System.Management;
using System.Windows.Forms;

namespace Laba_4
{
    public partial class USBView : Form
    {
        private const int WM_DEVICECHANGE = 0X219;//необходим для уведомления программы , что устройство подключилось 
        private static readonly Manager _manager = new Manager();
        private List<Usb> _deviceList, old_deviceList;
        private List<USBDeviceInfo> oldListDevices;

        protected override void WndProc(ref Message m)//вызывается при изменении конфигурации портов
        {
            base.WndProc(ref m);
            if (m.Msg == WM_DEVICECHANGE)
            {
                ReloadForm(false);
            }
        }

        public USBView()
        {
            InitializeComponent();
            ejectButton.Enabled = false;
        }

        private void LoadForm(object sender, EventArgs e)
        {
            _deviceList = new List<Usb>();
            ReloadForm(true);
            timer.Enabled = true;//запускаем таймер
        }
        private bool findDefference(List<USBDeviceInfo> deviceList)
        {
            if (deviceList.Count != oldListDevices.Count) return true;
            for (int i = 0; i < deviceList.Count; i++)
            {
                if (deviceList[i].Description != oldListDevices[i].Description) return true;
            }
            return false;
        }
        private bool findDefferenceFlash()
        {
            if (_deviceList.Count != old_deviceList.Count) return true;
            for (int i = 0; i < _deviceList.Count; i++)
            {
                if (_deviceList[i].DeviceName != old_deviceList[i].DeviceName) return true;
            }
            return false;
        }
        private void ReloadForm(bool flag)
        {
            _deviceList = _manager.DeviseListCreate();
            if (old_deviceList == null || findDefferenceFlash())
            {
                usbList.Items.Clear();
                foreach (Usb device in _deviceList)
                {
                    var deviceInfo = new ListViewItem(device.DeviceName);
                    usbList.Items.Add(deviceInfo);
                }
                old_deviceList = _deviceList; 
            }
            if (flag)
            {
                var deviceList = GetUSBDevices();
                if (oldListDevices == null || findDefference(deviceList))
                {
                    usbDevices.Items.Clear();
                    foreach (var dev in deviceList)
                    {
                        usbDevices.Items.Add(dev.Description);
                    }
                }
                oldListDevices = deviceList;
            }

        }

        private void TickTimer(object sender, EventArgs e)//по окончания работы таймера
        {
            ReloadForm(true);
        }
        private void eject(Usb Device)
        {
            if (!Device.EjectDevice())
            {
                MessageBox.Show("Can't eject this device", "Info", MessageBoxButtons.OK);
            }
            else
            {
                MessageBox.Show("Device was eject", "Info", MessageBoxButtons.OK);
            }
            ReloadForm(true);
        }
        private void ExecuteDevice(object sender, MouseEventArgs e)
        {
            eject(_deviceList[usbList.HitTest(e.Location).Item.Index]);//по двойному нажатию на девайс пытается его извлечь
        }
        private void UsbList_MouseClick(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            ListViewItem temp = usbList.FocusedItem;
            if (temp != null)
                ejectButton.Enabled = true;
            else ejectButton.Enabled = false;
        }

        private void ChangeButtonStatus(object sender, System.EventArgs e)
        {
            ListViewHitTestInfo temp = usbList.HitTest(new Point(MousePosition.X, MousePosition.Y));
            if (temp.Item != null)
                ejectButton.Enabled = true;
            else ejectButton.Enabled = false;
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (usbList.FocusedItem.Index == -1) return;
            eject(_deviceList[usbList.FocusedItem.Index]);
            ejectButton.Enabled = false;
        }

        static List<USBDeviceInfo> GetUSBDevices()
        {
            List<USBDeviceInfo> devices = new List<USBDeviceInfo>();

            ManagementObjectCollection collection;
           
           using (var searcher = new ManagementObjectSearcher(@"Select * From Win32_USBHub"))
                collection = searcher.Get();
               
                
            List<string> propertys = new List<string>();
            foreach (var device in collection)
            {
                string prop1 = device.GetText(TextFormat.Mof);
                propertys.Add(prop1);
                devices.Add(new USBDeviceInfo(
                (string)device.GetPropertyValue("DeviceID"),
                (string)device.GetPropertyValue("PNPDeviceID"),
                (string)device.GetPropertyValue("Description")
                ));
            }

            collection.Dispose();
            

            return devices;
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
    }


    class USBDeviceInfo
    {
        public USBDeviceInfo(string deviceID, string pnpDeviceID, string description)
        {
            this.DeviceID = deviceID;
            this.PnpDeviceID = pnpDeviceID;
            this.Description = description;
        }
        public string DeviceID { get; private set; }
        public string PnpDeviceID { get; private set; }
        public string Description { get; private set; }
    }
    
}