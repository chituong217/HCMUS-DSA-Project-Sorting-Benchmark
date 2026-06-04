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
Bài A: 
* Thuật toán lựa chọn lần 1: Radix sort.
* Phương pháp tối ưu: biến thể radix sort hệ số 256. 
* Lí do: phép tính chia lấy phần dư (modulo) dù theo nguyên lí vẫn sẽ được xử lí với độ phức tạp thời gian là O(1) tuy nhiên hệ đếm tự nhiên của máy tính là hệ nhị phân, phép tính modulo sẽ ép máy tính xử lí theo hệ thập phân và mất nhiều thời gian hơn để xử lí. Việc chọn một cơ số là lũy thừa của 2 sẽ giúp chúng ta bỏ qua phép tính modulo. Vì đề bài có đầu vào là số nguyên 32 bit, tương đương 8 byte, nên ta sẽ chọn cơ số 256.

Bài B:
* Thuật toán lựa chọn lần 1: Radix sort.
* Phương pháp tối ưu: biến thể radix sort phần tử quan trọng nhất (most signficant digit).
* Lí do: đề bài cho biết điều kiện đầu vào là các xâu chỉ có chữ cái tiếng anh viết thường, khi này các chữ cái sẽ có thứ tự và có thể xem đây bảng chữ cái viết thường là hệ số và một xâu là một số trong hệ này. Từ đó áp dụng radix sort với các bucket là chữ cái từ a tới z.

Bài C:
Bucket Sort kết hợp Radix Sort LSD

Các chuỗi được nhóm theo độ dài vào các bucket riêng (vector<vector<int>> byLen), sau đó trong mỗi bucket, vì tất cả chuỗi có cùng độ dài L, em chạy Radix Sort LSD duyệt ngược từ ký tự cuối về đầu. Lợi thế ở đây là biết trước độ dài nên hoàn toàn bỏ được các lệnh kiểm tra ký tự \0 trong vòng lặp phân phối, không còn nhánh if/else thừa, tốc độ nhờ vậy khá ổn.

## Cách sinh test case
Mục tiêu của bộ test này không phải là sinh dữ liệu ngẫu nhiên, mà là đánh sập các thuật toán Quick Sort dùng chốt pivot cố định và các hàm so sánh tự chế của những nhóm khác trong lớp.

Với bài số nguyên, nhóm tạo một mảng xếp giảm dần để ép các cài đặt Quick Sort lặp đủ N tầng đệ quy, đẩy thời gian chạy lên tối đa. Nhóm cũng thiết kế một test chỉ đan xen đúng hai số 1 và 2 để làm rối loạn các hàm chia mảng partition. Bẫy hiểm nhất là test thứ 5, chỉ in ra số lớn nhất (2147483647) và nhỏ nhất (-2147483648) của kiểu int 32-bit. Rất nhiều người quen tay viết hàm so sánh bằng phép trừ a trừ b. Khi gặp test này, máy tính sẽ bị tràn bộ nhớ và cho ra kết quả sai hoàn toàn.

Với mảng chuỗi, phép so sánh từng chữ cái là nơi dễ bị nghẽn nhất. Nhóm sinh ra các chuỗi dài 100 ký tự có 99 chữ cái đầu giống hệt nhau. Máy tính của các nhóm sẽ phải lặp qua 99 chữ cái đó vô ích chỉ để thấy sự khác biệt ở ký tự cuối cùng. Riêng ở bài C, nhóm lồng ghép một chuỗi ngắn làm tiền tố cho một chuỗi dài để ép thuật toán phải duyệt hết độ dài chuỗi ngắn mới phát hiện ra điểm khác biệt.

## Benchmark 2
Bài A:
* Thuật toán lựa chọn lần 2: Radix sort hệ số 256.
* Phương pháp tối ưu: giữ nguyên từ lần 1
Bài B:
* Thuật toán lựa chọn lần 2: Radix sort phần tử quan trọng nhất.
* Phương pháp tối ưu: giữ nguyên từ lần 1

Bài C:
Lần này em không sử dụng cấu trúc Bucket + Radix Sort và viết lại theo hướng tối ưu 3 yếu tố:

1. Đọc, ghi dữ liệu theo khối

Thay vì dùng cin,cout sinh ra nhiều system call lẻ tẻ, em khai báo hai mảng tĩnh in_buf và out_buf kích thước lớn (1 << 24 bytes, tức khoảng 16.7MB), rồi dùng fread và fwrite để nạp và xuất toàn bộ dữ liệu trong một lần duy nhất.

2. Dùng Memory Pool thay cho cấp phát động

Ở lần 1, string cấp phát bộ nhớ động liên tục khiến dữ liệu nằm rải rác trên heap, tăng khả năng cache miss. Lần 2, em nén toàn bộ nội dung chuỗi vào một mảng 1 chiều liên tục duy nhất char pool[MAX_CHARS], kèm theo một struct Str nhỏ gọn chỉ lưu start và len. Dữ liệu giờ nằm liền kề nhau trong RAM, CPU tận dụng được L1/L2 cache tốt hơn nhiều so với trước.

3. So sánh bằng memcmp tận dụng SIMD

Dù quay về mergesort (O(nlogn)), có vẻ không tối ưu được như Radix Sort tuyến tính ở lần 1, nhưng hàm so sánh lúc này dùng memcmp(pool + start, pool + other.start, len). memcmp được tối ưu về mặt assembly với các thanh ghi SIMD, so sánh nhiều byte song song trong một lần. Kết quả thực tế cho thấy lợi ích từ cache hit tốt và SIMD bù đắp hoàn toàn cho phần phức tạp thuật toán tăng thêm — thời gian chạy thực tế của lần 2 vượt hẳn lần 1.
