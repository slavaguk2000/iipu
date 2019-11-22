using System.Linq;
using UsbEject;

namespace Laba_4
{
    class Usb
    {
        public string DeviceName { get; set; }
        public bool IsMtpDevice { get; set; }
      
        public bool EjectDevice()
        {
            string tempName = DeviceName.Remove(2);//получаем том девавйса
            Volume ejectedDevice = new VolumeDeviceClass().SingleOrDefault(v => v.LogicalDrive == tempName);//получаем значение состояния девайса
            if (!IsMtpDevice)
            {
                ejectedDevice.Eject(false);
                ejectedDevice = new VolumeDeviceClass().SingleOrDefault(v => v.LogicalDrive == tempName);//повторное подключение к девайсу после поытки извлечения
            }
            else
            {
                return false;
            }
            return ejectedDevice == null;
        }
    }
}
