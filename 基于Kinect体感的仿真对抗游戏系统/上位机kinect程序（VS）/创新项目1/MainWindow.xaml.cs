using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Microsoft.Kinect;
using System.Linq;
using System.IO;
using System.IO.Ports;
using System.Collections.Generic;
using Microsoft.Speech.AudioFormat;
using Microsoft.Speech.Recognition;

namespace 创新项目1
{
    public partial class MainWindow : Window
    {
        public static KinectSensor sensor;
        public static Ellipse ellipse2;
        byte[] pixelData;
        public static Skeleton[] skeletons;
        public static SerialPort _serialPort;//定义一个串口变量
        private SpeechRecognitionEngine speechEngine;//语音参数

        public MainWindow()
        {
            InitializeComponent();
            
            Dictionary<int, string> mydic = new Dictionary<int, string>() 
            { 
                { 1, "COM1" }, 
                { 2, "COM2" }, 
                { 3, "COM3" },
                { 4, "COM4" }, 
                { 5, "COM5" }, 
                { 6, "COM6" },
                { 7, "COM7" }, 
                { 8, "COM8" }, 
                { 9, "COM9" } 
            };
            comboBox1.ItemsSource = mydic;
            comboBox1.SelectedValuePath = "Key"; 
            comboBox1.DisplayMemberPath = "Value";
            comboBox1.SelectedIndex = 0;
            _serialPort = new SerialPort();//实例化一个串口变量
            //Runtime initialization is handled when the window is opened. When the window
            //is closed, the runtime MUST be unitialized.
            this.Loaded += new RoutedEventHandler(MainWindow_Loaded);
            this.Unloaded += new RoutedEventHandler(MainWindow_Unloaded);       
        }

        void runtime_SkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            bool receivedData = false;

            using (SkeletonFrame SFrame = e.OpenSkeletonFrame())
            {
                if (SFrame == null)
                {
                    return;// The image processing took too long. More than 2 frames behind.
                }
                else
                {
                    skeletons = new Skeleton[SFrame.SkeletonArrayLength];
                    SFrame.CopySkeletonDataTo(skeletons);
                    receivedData = true;
                }
            }

            if (receivedData)
            {
                GuGeZhuiZong.shoubikongzhi();

                Canvas.SetLeft(leftHand, GuGeZhuiZong.leftHand_s.X);
                Canvas.SetTop(leftHand, GuGeZhuiZong.leftHand_s.Y);
                Canvas.SetLeft(rightHand, GuGeZhuiZong.rightHand_s.X);
                Canvas.SetTop(rightHand, GuGeZhuiZong.rightHand_s.Y);
                
            }
        }

        void MainWindow_Unloaded(object sender, RoutedEventArgs e)
        {
            if(sensor != null)  sensor.Stop();
            if (null != this.speechEngine)
            {
                this.speechEngine.SpeechRecognized -= SpeechRecognized;
                this.speechEngine.RecognizeAsyncStop();
            }
        }
        
        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            foreach (var potentialSensor in KinectSensor.KinectSensors)
            {
                if (potentialSensor.Status == KinectStatus.Connected)
                {
                    sensor = potentialSensor;
                    break;
                }
            }

            if (null != sensor)
            {
                sensor.ColorStream.Enable();
                sensor.SkeletonStream.Enable();

                sensor.SkeletonFrameReady += runtime_SkeletonFrameReady;
                sensor.ColorFrameReady += runtime_VideoFrameReady;
                
                try
                {
                    sensor.Start();
                }
                catch (IOException)
                {
                    sensor = null;
                }
            }

            if (null == sensor)
            {
                this.textBox1.Text += "kinect启动出现问题\n";
            }

            yuyin();
        }

        private void yuyin()
        {
            RecognizerInfo ri = YuYinBuFen.GetKinectRecognizer();

            if (null != ri)
            {
              // this.speechEngine = new SpeechRecognitionEngine(ri.Id);

                var directions = new Choices();
                directions.Add(new SemanticResultValue("forward", "FORWARD"));
                directions.Add(new SemanticResultValue("forwards", "FORWARD"));
                directions.Add(new SemanticResultValue("straight", "FORWARD"));
                directions.Add(new SemanticResultValue("backward", "BACK"));
                directions.Add(new SemanticResultValue("backwards", "BACK"));
                directions.Add(new SemanticResultValue("back", "BACK"));
                directions.Add(new SemanticResultValue("turn left", "LEFT"));
                directions.Add(new SemanticResultValue("turn right", "RIGHT"));
                directions.Add(new SemanticResultValue("left", "LEFT"));
                directions.Add(new SemanticResultValue("right", "RIGHT"));

                var gb = new GrammarBuilder { Culture = ri.Culture };
                gb.Append(directions);

                var g = new Grammar(gb);
              // speechEngine.LoadGrammar(g);

              // speechEngine.SpeechRecognized += SpeechRecognized;
               
              //  speechEngine.SetInputToAudioStream(
               //     sensor.AudioSource.Start(), new SpeechAudioFormatInfo(EncodingFormat.Pcm, 16000, 16, 1, 32000, 2, null));
                //speechEngine.RecognizeAsync(RecognizeMode.Multiple);
           }
            else
            {
                this.textBox1.Text += "语音资源打开失败\n";
            }
        }

        private void SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            // Speech utterance confidence below which we treat speech as if it hadn't been heard
            const double ConfidenceThreshold = 0.99;

            if (e.Result.Confidence >= ConfidenceThreshold)
            {
                this.textBox1.Text += e.Result.Semantics.Value.ToString() + "\n";
                switch (e.Result.Semantics.Value.ToString())
                {
                    case "FORWARD":
                        GuGeZhuiZong.Write("a");
                        break;

                    case "BACK":
                        GuGeZhuiZong.Write("b");
                        break;

                    case "LEFT":
                        GuGeZhuiZong.Write("2");
                        break;

                    case "RIGHT":
                        GuGeZhuiZong.Write("3");
                        break;
                }
            }
        }

        void runtime_VideoFrameReady(object sender, ColorImageFrameReadyEventArgs e)
        {
            bool receivedData = false;

            using (ColorImageFrame CFrame = e.OpenColorImageFrame())
            {
                if (CFrame == null)
                {
                    // The image processing took too long. More than 2 frames behind.
                }
                else
                {
                    pixelData = new byte[CFrame.PixelDataLength];
                    CFrame.CopyPixelDataTo(pixelData);
                    receivedData = true;
                }
            }

            if (receivedData)
            {
                BitmapSource source = BitmapSource.Create(640, 480, 96, 96,
                        PixelFormats.Bgr32, null, pixelData, 640 * 4);
                //videoImage.
                videoImage.Source = source;
            }
        }

        private void textBox1_TextChanged(object sender, TextChangedEventArgs e)
        {
            this.textBox1.ScrollToEnd();
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            if (sensor == null) return;
            if (!sensor.IsRunning) return;
            if (sensor.ElevationAngle <= sensor.MaxElevationAngle - 5)
            {
                button1.IsEnabled = false;
                sensor.ElevationAngle += 5;
                button1.IsEnabled = true;
            }
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            if (sensor == null) return;
            if (!sensor.IsRunning) return;
            if (sensor.ElevationAngle >= sensor.MinElevationAngle + 5)
            {
                button2.IsEnabled = false;
                sensor.ElevationAngle -= 5;
                button2.IsEnabled = true;
            }
        }

        private void button3_Click(object sender, RoutedEventArgs e)
        {
            
            if (!_serialPort.IsOpen)
            {
                Init.InitSerialPort(_serialPort, Convert.ToInt32(comboBox1.SelectedValue));
                if (_serialPort.IsOpen)
                    button3.Content = "关闭串口";
            }
            else
            {
                _serialPort.Close();
                button3.Content = "打开串口";
            }
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {

        }
    }
}
