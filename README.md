# Báo cáo đồ án 1: Sorting benchmark

## Thông tin chung
Tên môn học: Cấu trúc dữ liệu và giải thuật
Thời gian: Học kỳ II, năm học 2025 - 2026
Đơn vị: Khoa Công nghệ Thông tin - Trường Đại học Khoa học Tự nhiên (HCMUS)
Nhóm sinh viên thực hiện:
Nguyễn Lê Chí Tường (25120465)
Đoàn Hoàng Việt (25120469)
Lê Dương Hồng Quân (25120424)

## Benchmark 1
Ở lần chạy đầu tiên, tụi mình muốn vượt qua giới hạn O(N log N) của các thuật toán so sánh thông thường. Nhóm quyết định dùng Radix Sort cho cả 3 bài vì độ phức tạp của nó là tuyến tính O(N * K).

Với bài A, nhóm dùng Radix Sort hệ số 256. Khuyết điểm lớn nhất của Radix Sort thông thường là phép chia lấy dư (modulo). Hệ đếm tự nhiên của máy tính là nhị phân, ép nó chia modulo theo hệ thập phân sẽ tốn rất nhiều thời gian. Chọn cơ số 256 (lũy thừa của 2) cho phép tụi mình dùng thẳng toán tử dịch bit (bitwise) và loại bỏ hoàn toàn phép modulo. Việc xử lý số âm cũng được xử lý tại chỗ: chỉ cần đẩy các byte từ 128-255 (số âm bù hai) lên trước nhóm 0-127 ở vòng lặp cuối cùng.

Với bài B, nhóm cài MSD Radix Sort (phân vùng từ trái sang phải). Các chữ cái tiếng Anh viết thường được xem như một hệ cơ số 26, dựa vào đó để chia chuỗi vào các rổ từ 'a' đến 'z'.

Với bài C, nhóm kết hợp Bucket Sort và Radix Sort LSD. Đầu tiên, chia các chuỗi vào từng rổ theo độ dài. Khi vào chung một rổ, các chuỗi đã dài bằng nhau, lúc này tụi mình cứ chạy Radix Sort duyệt ngược từ ký tự cuối lên đầu. Nhờ biết trước độ dài chuỗi, chương trình không cần rẽ nhánh if/else để kiểm tra ký tự kết thúc, giúp tiết kiệm được một lượng lớn nhịp CPU.

## Cách sinh test case
Chương trình test_gen.cpp tuân thủ chuẩn C++23 và nhận tham số trực tiếp từ dòng lệnh (ví dụ: test_gen.exe int 3). Nhóm loại bỏ hàm rand() của C vì nó dễ bị lệch dư và chỉ sinh số nhỏ. Thay vào đó, tụi mình xài thuật toán Mersenne Twister (mt19937) để tạo ra tập dữ liệu phân phối đều.

Mục tiêu của bộ test là đánh sập QuickSort và các hàm so sánh chuỗi tự chế.
Ở bài số nguyên, test 2 sinh mảng giảm dần, test 3 sinh mảng toàn số 1 và 2 đan xen, test 4 là mảng 100.000 số giống nhau hoàn toàn. Nếu các bài nộp khác dùng QuickSort với chốt (pivot) cố định ở đầu hoặc cuối mảng, cây đệ quy sẽ bị lệch hoàn toàn sang một bên. Thuật toán sẽ thoái hóa thành O(N^2), gây tràn stack hoặc lố thời gian. Test 5 đan xen số lớn nhất (2147483647) và nhỏ nhất (-2147483648) của kiểu 32-bit. Ai quen tay viết hàm so sánh bằng phép trừ sẽ bị tràn số và in ra kết quả sai.

Ở bài chuỗi, nút thắt luôn nằm ở chi phí duyệt chữ cái. Test 2 tạo 100.000 chuỗi dài 100 ký tự, trong đó 99 ký tự đầu giống hệt nhau. Code dùng std::sort hoặc strcmp bình thường sẽ phải duyệt qua 99 ký tự này một cách lãng phí ở mỗi phép so sánh. Riêng bài C, test 4 tung vào các chuỗi có chiều dài lộn xộn, kết hợp với các chuỗi trùng tiền tố. Mục đích của test này là gây trượt bộ đệm (cache miss) nếu đối thủ cấp phát dữ liệu chuỗi rời rạc trên heap.

## Benchmark 2
Sau lần 1, tụi mình nhận ra bài A và B dùng Radix Sort thực chất đã tối ưu trần về mặt thuật toán. Vấn đề làm code chậm không nằm ở vòng lặp nữa mà nằm ở kỹ thuật xử lý đầu vào. Nhóm quyết định giữ nguyên thuật toán và chỉ viết lại cơ chế Fast I/O để đọc dữ liệu nhanh hơn.

Sự lột xác lớn nhất nằm ở bài C. Lần này nhóm bỏ Bucket + Radix Sort, quay về Merge Sort truyền thống nhưng ép phần cứng chạy tối đa bằng 3 kỹ thuật.

Thứ nhất, đọc ghi theo khối. Dùng cin hoặc cout sinh ra quá nhiều system call. Tụi mình khai báo hẳn một mảng tĩnh 16.7MB, rồi gọi fread và fwrite nạp xuất toàn bộ input/output trong một lần duy nhất.

Thứ hai, nhóm tự làm Memory Pool thay cho cấp phát động. Ở lần 1, việc dùng kiểu string cấp phát bộ nhớ liên tục làm dữ liệu nằm rải rác. Lần 2, toàn bộ nội dung chuỗi được nén vào một mảng ký tự 1 chiều duy nhất, đi kèm một struct nhẹ chỉ lưu vị trí bắt đầu và chiều dài. Dữ liệu giờ đây nằm liền kề nhau trong RAM, giúp CPU bắt được L1/L2 cache tốt hơn hẳn.

Thứ ba, dùng SIMD để so sánh. Dù Merge Sort có độ phức tạp O(N log N) thua Radix Sort tuyến tính, nhưng tụi mình dùng memcmp để so sánh nội dung chuỗi. Hàm memcmp được tối ưu ở mức assembly bằng các thanh ghi SIMD, cho phép đối chiếu nhiều byte cùng lúc. Tốc độ truy xuất cache và sức mạnh của SIMD dư sức bù đắp cho phần thuật toán, ép thời gian chạy thực tế của lần 2 vượt xa cả lần 1.
