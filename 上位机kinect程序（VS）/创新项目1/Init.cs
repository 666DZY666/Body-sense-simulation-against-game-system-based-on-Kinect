using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO.Ports;
using System.Windows;

namespace 创新项目1
{
    class Init
    {
        public static void InitSerialPort(SerialPort _serialPort,int com)//串口初始化函数
        {
            try
            {
                if (_serialPort.IsOpen) return;
                switch(com)
                {
                    case 1: _serialPort.PortName = "COM1"; break;
                    case 2: _serialPort.PortName = "COM2"; break;
                    case 3: _serialPort.PortName = "COM3"; break;
                    case 4: _serialPort.PortName = "COM4"; break;
                    case 5: _serialPort.PortName = "COM5"; break;
                    case 6: _serialPort.PortName = "COM6"; break;
                    case 7: _serialPort.PortName = "COM7"; break;
                    case 8: _serialPort.PortName = "COM8"; break;
                    case 9: _serialPort.PortName = "COM9"; break;
                }
                _serialPort.BaudRate = 9600;
                _serialPort.Parity = (Parity)Enum.Parse(typeof(Parity), "None");
                _serialPort.DataBits = 8;
                _serialPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), "One");
                _serialPort.Handshake = (Handshake)Enum.Parse(typeof(Handshake), "None");

                // Set the read/write timeouts
                _serialPort.ReadTimeout = 500;
                _serialPort.WriteTimeout = 500;

                _serialPort.Open();
            }
            catch (Exception)
            {
                MessageBox.Show(_serialPort.PortName + "串口打开失败");
            }
        }

        public static int JiaoDu(double Ax, double Ay, double Bx, double By, double Cx, double Cy)
        {
            double a, b, c, X; int x;
            a = Math.Sqrt(((Cx - Bx) * (Cx - Bx)) + ((Cy - By) * (Cy - By)));
            b = Math.Sqrt(((Ax - Cx) * (Ax - Cx)) + ((Ay - Cy) * (Ay - Cy)));
            c = Math.Sqrt(((Ax - Bx) * (Ax - Bx)) + ((Ay - By) * (Ay - By)));
            X = (a * a) + (b * b) - (c * c);
            X = X / (2 * a * b);
            X = 180 * Math.Acos(X) / 3.1415926;
            x = (int)X;
            return x;
        }

        public static int JiaoDu3(double Ax, double Ay, double Az, double Bx, double By, double Bz, double Cx, double Cy, double Cz)
        {
            double a, b, c, X; int x;
            a = Math.Sqrt(((Cx - Bx) * (Cx - Bx)) + ((Cy - By) * (Cy - By)) + ((Cz - Bz) * (Cz - Bz)));
            b = Math.Sqrt(((Ax - Cx) * (Ax - Cx)) + ((Ay - Cy) * (Ay - Cy)) + ((Az - Cz) * (Az - Cz)));
            c = Math.Sqrt(((Ax - Bx) * (Ax - Bx)) + ((Ay - By) * (Ay - By)) + ((Az - Bz) * (Az - Bz)));
            X = (a * a) + (b * b) - (c * c);
            X = X / (2 * a * b);
            X = 180 * Math.Acos(X) / 3.1415926;
            x = (int)X;
            return x;
        }

        public static int JunZhi(int n1, int n2, int n3, int n4, int n5)
        {
            int max, min, avr;
            max = Math.Max(Math.Max(Math.Max(Math.Max(n1, n2), n3), n4), n5);
            min = Math.Min(Math.Min(Math.Min(Math.Min(n1, n2), n3), n4), n5);
            avr = (n1 + n2 + n3 + n4 + n5 - max - min) / 3;
            return avr;
        }
    }
}
