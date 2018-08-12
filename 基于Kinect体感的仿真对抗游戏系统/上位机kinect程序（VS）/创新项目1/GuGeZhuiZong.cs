using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Kinect;
using System.Threading;
using System.Diagnostics;
using System.Windows.Controls;
using System.Windows;




namespace 创新项目1
{
    class GuGeZhuiZong
    {
        public static float x = 0, y = 0, z = 0;
        static int j = 0; static char a = '0';
        public static Point leftHand_s, rightHand_s;
        public static void shoubikongzhi()//手臂控制函数
        {
            Skeleton currentSkeleton = (from s in MainWindow.skeletons
                                        where s.TrackingState == SkeletonTrackingState.Tracked
                                        select s).FirstOrDefault();
        if (currentSkeleton != null)
            {

                SkeletonPoint head = currentSkeleton.Joints[JointType.Head].Position;                          //库函数获取包括头部、肩部、肘部、手部、臀部、膝部在内16个节点的空间三维坐标
                SkeletonPoint shoulderCenter = currentSkeleton.Joints[JointType.ShoulderCenter].Position;
                SkeletonPoint shoulderLeft = currentSkeleton.Joints[JointType.ShoulderLeft].Position;
                SkeletonPoint shoulderRight = currentSkeleton.Joints[JointType.ShoulderRight].Position;
                SkeletonPoint elbowLeft = currentSkeleton.Joints[JointType.ElbowLeft].Position;
                SkeletonPoint elbowRight = currentSkeleton.Joints[JointType.ElbowRight].Position;
                SkeletonPoint wristLeft = currentSkeleton.Joints[JointType.WristLeft].Position;
                SkeletonPoint wristRight = currentSkeleton.Joints[JointType.WristRight].Position;
                SkeletonPoint leftHand = currentSkeleton.Joints[JointType.HandLeft].Position;
                SkeletonPoint rightHand = currentSkeleton.Joints[JointType.HandRight].Position;
                SkeletonPoint spine = currentSkeleton.Joints[JointType.Spine].Position;
                SkeletonPoint hipcenter = currentSkeleton.Joints[JointType.HipCenter].Position;
                SkeletonPoint hipLeft = currentSkeleton.Joints[JointType.HipLeft].Position;
                SkeletonPoint hipRight = currentSkeleton.Joints[JointType.HipRight].Position;
                SkeletonPoint kneeLeft = currentSkeleton.Joints[JointType.KneeLeft].Position;
                SkeletonPoint kneeRight = currentSkeleton.Joints[JointType.KneeRight].Position;

                leftHand_s = SkeletonPointToScreen(leftHand);                                                  //在调试窗仅显示两个手部节点
                rightHand_s = SkeletonPointToScreen(rightHand);


                    double DistanceBetweenHands = Math.Sqrt((rightHand.Y - leftHand.Y) * (rightHand.Y - leftHand.Y) + (rightHand.X - leftHand.X) * (rightHand.X - leftHand.X));
                    if (DistanceBetweenHands < 0.4 && rightHand.Y - spine.Y < 0.2 && spine.Y - rightHand.Y < 0.2 && leftHand.Y - spine.Y < 0.2 && spine.Y - leftHand.Y < 0.2)       //电机控制手势动作区域限定
                    {
                        if (rightHand.Y - leftHand.Y > 0.12)                                                    //电机控制部分
                        {
                            Write("2");
                            Debug.WriteLine("左转");
                        }
                        
                        if (leftHand.Y - rightHand.Y > 0.12)
                        {
                            Write("3");
                            Debug.WriteLine("右转");
                        }
                        
                        if (rightHand.Z - leftHand.Z > 0.12 && rightHand.Z - leftHand.Z < 0.26)
                        {
                            Write("1");
                            Debug.WriteLine("后退");
                        }
                        
                        if (leftHand.Z - rightHand.Z > 0.12 && leftHand.Z - rightHand.Z < 0.26)
                        {
                            Write("0");
                            Debug.WriteLine("前进");
                        }

                        if (rightHand.Z - leftHand.Z > 0.26 )
                        {
                            Write("p");
                            Debug.WriteLine("大后退");
                        }

                        if (leftHand.Z - rightHand.Z > 0.26)
                        {
                            Write("4");
                            Debug.WriteLine("大前进");
                        }
                    }

                    else                                                                                         //舵机控制部分
                    {
                        double chongdi = 0.13;
                        if (elbowRight.Y - rightHand.Y > 0.2 && shoulderRight.Y - elbowRight.Y > 0.15)
                        {
                            //if (a != '9')
                            //{
                                Write("9");
                                Debug.WriteLine("右手初始化");
                            //}
                            //a = '9';
                        }

                        if (rightHand.Y - head.Y > 0 && elbowRight.X - shoulderRight.X > 0.1)
                        {
                            //if (a != '5')
                            //{
                                Write("5");
                                Debug.WriteLine("右手高举");
                            //}
                            //a = '5';
                        }

                        if (shoulderRight.Y - elbowRight.Y < chongdi && elbowRight.Y - shoulderRight.Y < chongdi && shoulderRight.X - elbowRight.X < chongdi && elbowRight.X - shoulderRight.X < chongdi && shoulderRight.Y - rightHand.Y < chongdi && rightHand.Y - shoulderRight.Y < chongdi && shoulderRight.X - rightHand.X < chongdi && rightHand.X - shoulderRight.X < chongdi)
                        {
                            //if (a != 'j')
                            //{
                                Write("j");
                                Debug.WriteLine("右手前伸");
                            //}
                            //a = 'j';
                        }

                        if (shoulderRight.Z - elbowRight.Z > 0.1 && elbowRight.X - rightHand.X > 0.1)
                        {
                            //if (a != 'a')
                            //{
                                Write("a");
                                Debug.WriteLine("右勾手");
                            //}
                            //a = 'a';
                        }
                                           
                        if (elbowRight.Y - rightHand.Y > 0.05 && elbowRight.Y - rightHand.Y < 0.2 && shoulderRight.Y - elbowRight.Y > 0.05 && shoulderRight.Y - elbowRight.Y < 0.15)
                        {
                            //if (a != '7')
                            //{
                                Write("7");
                                Debug.WriteLine("右手下举");
                            //}
                            //a = '7';
                        }

                        if (elbowLeft.Y - leftHand.Y > 0.2 && shoulderLeft.Y - elbowLeft.Y > 0.15)
                        {
                            //if (a != 'i')
                            //{
                                Write("i");
                                Debug.WriteLine("左手初始化");
                            //}
                            //a = 'i';
                        }
                       
                        if (leftHand.Y - head.Y > 0 && shoulderLeft.X - elbowLeft.X > 0.1)
                        {
                            //if (a != 'e')
                            //{
                                Write("e");
                                Debug.WriteLine("左手高举");
                            //}
                            //a = 'e';
                        }

                        if (shoulderLeft.Y - elbowLeft.Y < chongdi && elbowLeft.Y - shoulderLeft.Y < chongdi && shoulderLeft.X - elbowLeft.X < chongdi && elbowLeft.X - shoulderLeft.X < chongdi && shoulderLeft.Y - leftHand.Y < chongdi && leftHand.Y - shoulderLeft.Y < chongdi && shoulderLeft.X - leftHand.X < chongdi && leftHand.X - shoulderLeft.X < chongdi)
                        {
                            //if (a != 'm')
                            //{
                                Write("m");
                                Debug.WriteLine("左手前伸");
                            //}
                            //a = 'm';
                        }

                        if (shoulderLeft.Z - elbowLeft.Z > 0.1 && leftHand.X - elbowLeft.X > 0.1)
                        {
                            //if (a != 'b')
                            //{
                                Write("b");
                                Debug.WriteLine("左勾手");
                            //}
                            //a = 'b';
                        }
                        
                        if (elbowLeft.Y - leftHand.Y > 0.05 && elbowLeft.Y - leftHand.Y < 0.2 && shoulderLeft.Y - elbowLeft.Y > 0.05 && shoulderLeft.Y - elbowLeft.Y < 0.15)
                        {
                            //if (a != 'g')
                            //{
                                Write("g");
                                Debug.WriteLine("左手下举");
                            //}
                            //a = 'g';
                        }
                    }
            }
        }

        public static void Write(string s)
        {
            if (MainWindow._serialPort.IsOpen)
            {
                MainWindow._serialPort.Write(s);
            }
        }
        /// <summary>
        /// Maps a SkeletonPoint to lie within our render space and converts to Point
        /// </summary>
        /// <param name="skelpoint">point to map</param>
        /// <returns>mapped point</returns>
        public static Point SkeletonPointToScreen(SkeletonPoint skelpoint)
        {
            // Convert point to depth space.  
            // We are not using depth directly, but we do want the points in our 640x480 output resolution.
            DepthImagePoint depthPoint = MainWindow.sensor.CoordinateMapper.MapSkeletonPointToDepthPoint(skelpoint, DepthImageFormat.Resolution640x480Fps30);
            if (depthPoint.X <= 650 && depthPoint.Y <= 490)
                return new Point(depthPoint.X + 10, depthPoint.Y + 10);
            else return new Point(650, 490);
        }
    }
}
