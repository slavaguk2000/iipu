using System.Collections.Generic;
using System.Linq;
using System.IO;
using MediaDevices;

namespace Laba_4
{
    class Manager
    {
        public List<Usb> DeviseListCreate()
        {
            List<Usb> usbDevices = new List<Usb>();//список , который будет выводиться
            List<DriveInfo> diskDrives = DriveInfo.GetDrives().Where(d => d.IsReady && d.DriveType == DriveType.Removable).ToList();//из драйверинфо получаем устройства, которые подключены и являются внешними
            List<MediaDevice> mtpDrives = MediaDevice.GetDevices().ToList();//телефоны и тд
            foreach (var device in mtpDrives)//медиа девайсы
            {
                try
                {
                    device.Connect();//notfound exception
                    if (device.Protocol.Contains("MTP"))//поиск mtp девайсов
                    {
                        usbDevices.Add(new Usb()
                        {
                            DeviceName = device.Description,
                            IsMtpDevice = true
                        });
                    }
                }
                catch (FileNotFoundException)
                { }
            }
            foreach (DriveInfo drive in diskDrives)//для флешек
            {
                usbDevices.Add(new Usb()
                {
                    DeviceName = drive.Name,
                    IsMtpDevice = false
                });
            }
            return usbDevices;
        }
    }
}
