# Wireless-Sensor-Network_Hust_20221
Project for Wireless Sensor Network class in HUST 20221
## Cấu hình Edge
- Tải Docker về máy:  
Có nhiều lựa chọn để có thể cấu hình Thingsboard Edge trên máy tính ở đây nhóm lựa chọn sử dụng Docker for Windows
Các lựa chọn khác có thể tham khảo:
https://thingsboard.io/docs/user-guide/install/edge/installation-options/
- Chạy Thingsboard Edge trên máy theo file cấu hình sử dụng lệnh trên terminal theo hướng dẫn sau: https://thingsboard.io/docs/user-guide/install/edge/docker-windows/ 
- Truy nhập vào Thingsboard Edge sử dụng địa chỉ IP của máy mà docker chạy trên máy đó và sử dụng địa chỉ đó để kết nối Gateway
- Tạo Device trên Edge sẽ đồng bộ hóa với Cloud và copy ACCESS TOKEN của Device đó để đưa vào parameter của HTTP request

Tạo Device theo hướng dẫn: https://thingsboard.io/docs/edge/getting-started/
## Triển khai trên Thingsboard Cloud
- Sau khi tạo Device trên Edge thì sẽ được đồng bộ lên Cloud
- Tạo Rule chain để tạo và xóa cảnh báo khi thông số vượt ngưỡng https://thingsboard.io/docs/user-guide/rule-engine-2-0/tutorials/create-clear-alarms/
- Tạo Dashboard và cấu hình Widget để hiển thị và điều khiển: https://thingsboard.io/docs/user-guide/contribution/widgets-development/

Cấu hình bản tin để gửi bao gồm Method và params lệnh theo RPC ở phần Advanced của Control Widget (Hướng dẫn về RPC: https://thingsboard.io/docs/user-guide/rpc/)

Sau đó Assign Dashboard xuống Edge để đồng bộ 
## Triển khai Web và App
- Sử dụng trực tiếp trang Web và App do Thingsboard cung cấp chỉ cần đăng nhập vào tài khoản đã đăng ký


## Các Phần mềm và tool cần phải tải: 
- Mqttfx đây là tool cho phép tạo Client để kiểm tra gói tin trong quá trình phát triển, download đường link sau: https://iowin.net/en/mqtt-fx/
- Cài đặt IDE: Visual studio Code: https://code.visualstudio.com/download
               Platform IO trong extension của VScode
               ![image](https://user-images.githubusercontent.com/83686238/220578152-81848072-4d1e-48d4-9e55-b734bb5bd84f.png)

- Cài đặt Broker Local cho phép điều khiển Local: https://www.hivemq.com/docs/hivemq/4.8/user-guide/getting-started.html
fbclid=IwAR2prAcaJGY28_f3wrOxMZF1SMVCM9_FRGjOtTYSNgHKVWW66K8jHxGFr1Q#download
- Cài đặt phần mềm ESPtouch trên ứng dụng CHPlay để cấu hình Wifi cho thiết bị 
![image](https://user-images.githubusercontent.com/83686238/220579249-fb2c75d6-e7e8-47e9-b4f0-1ba0b838ecde.png)

## Tổ chức file trong folder Code
- Folder Code nằm trong nhánh "Code" của Repo dự án, tải về và giải nén
- 
![image](https://user-images.githubusercontent.com/83686238/220580238-cc6245a1-dc44-4507-b863-d7bd55901ad6.png)

- Dự án gồm 4 Node và 1 Gate do vậy sẽ có 4 folder về Node và 1 folder về Gateway được tổ chức file tương tự nhau nên sẽ chỉ phân tích folder Gateway
- Mỗi folder sẽ chứa main source code trong thư mục "src" bao gồm file main.cpp và các file.h khác; folder ".pio" sẽ chưa các thư viện hỗ trợ trong dự án; file "platformio.ini" sẽ bao gồm các cấu hình như monitor speed và monitor port cùng với install thư viện về dự án

![image](https://user-images.githubusercontent.com/83686238/220577655-75e574f0-ccc3-4ff4-8af0-9df44f0e8674.png)

- Sau khi đã download và cấu hình xong, nhấn vào "build" để compile code sau đó "upload" để nạp code
- 
![image](https://user-images.githubusercontent.com/83686238/220578524-87e6995f-822d-4aa7-9b8d-f78b24f5611a.png)

