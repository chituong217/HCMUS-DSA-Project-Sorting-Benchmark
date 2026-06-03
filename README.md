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
Chương trình test_gen.cpp tuân thủ chuẩn C++23 và nhận tham số trực tiếp từ dòng lệnh (ví dụ: test_gen.exe int 3). Nhóm loại bỏ hàm rand() của C vì nó dễ bị lệch dư và chỉ sinh số nhỏ. Thay vào đó, tụi mình xài thuật toán Mersenne Twister (mt19937) để tạo ra tập dữ liệu phân phối đều.

Mục tiêu của bộ test là đánh sập QuickSort và các hàm so sánh chuỗi tự chế.
Ở bài số nguyên, test 2 sinh mảng giảm dần, test 3 sinh mảng toàn số 1 và 2 đan xen, test 4 là mảng 100.000 số giống nhau hoàn toàn. Nếu các bài nộp khác dùng QuickSort với chốt (pivot) cố định ở đầu hoặc cuối mảng, cây đệ quy sẽ bị lệch hoàn toàn sang một bên. Thuật toán sẽ thoái hóa thành O(N^2), gây tràn stack hoặc lố thời gian. Test 5 đan xen số lớn nhất (2147483647) và nhỏ nhất (-2147483648) của kiểu 32-bit. Ai quen tay viết hàm so sánh bằng phép trừ sẽ bị tràn số và in ra kết quả sai.

Ở bài chuỗi, nút thắt luôn nằm ở chi phí duyệt chữ cái. Test 2 tạo 100.000 chuỗi dài 100 ký tự, trong đó 99 ký tự đầu giống hệt nhau. Code dùng std::sort hoặc strcmp bình thường sẽ phải duyệt qua 99 ký tự này một cách lãng phí ở mỗi phép so sánh. Riêng bài C, test 4 tung vào các chuỗi có chiều dài lộn xộn, kết hợp với các chuỗi trùng tiền tố. Mục đích của test này là gây trượt bộ đệm (cache miss) nếu đối thủ cấp phát dữ liệu chuỗi rời rạc trên heap.

## Benchmark 2
Bài A:
* Thuật toán lựa chọn lần 2: Radix sort hệ số 256.
* Phương pháp tối ưu: tối ưu đầu vào.
* Lí do: khi dữ liệu đầu vào lớn, nó sẽ trở thành một cản trở về thời gian chạy. Đôi khi code chạy chậm không phải vì thuật toán chưa tối ưu nhưng vì kĩ thuật xử lí đầu vào còn nhiều lỗ hỏng.

Bài B:
* Thuật toán lựa chọn lần 2: Radix sort phần tử quan trọng nhất.
* Phương pháp tối ưu: tối ưu đầu vào.
* Lí do: khi dữ liệu đầu vào lớn, nó sẽ trở thành một cản trở về thời gian chạy. Đôi khi code chạy chậm không phải vì thuật toán chưa tối ưu nhưng vì kĩ thuật xử lí đầu vào còn nhiều lỗ hỏng.

Bài C:
Lần này em không sử dụng cấu trúc Bucket + Radix Sort và viết lại theo hướng tối ưu 3 yếu tố:

1. Đọc, ghi dữ liệu theo khối

Thay vì dùng cin,cout sinh ra nhiều system call lẻ tẻ, em khai báo hai mảng tĩnh in_buf và out_buf kích thước lớn (1 << 24 bytes, tức khoảng 16.7MB), rồi dùng fread và fwrite để nạp và xuất toàn bộ dữ liệu trong một lần duy nhất.

2. Dùng Memory Pool thay cho cấp phát động

Ở lần 1, string cấp phát bộ nhớ động liên tục khiến dữ liệu nằm rải rác trên heap, tăng khả năng cache miss. Lần 2, em nén toàn bộ nội dung chuỗi vào một mảng 1 chiều liên tục duy nhất char pool[MAX_CHARS], kèm theo một struct Str nhỏ gọn chỉ lưu start và len. Dữ liệu giờ nằm liền kề nhau trong RAM, CPU tận dụng được L1/L2 cache tốt hơn nhiều so với trước.

3. So sánh bằng memcmp tận dụng SIMD

Dù quay về mergesort (O(nlogn)), có vẻ không tối ưu được như Radix Sort tuyến tính ở lần 1, nhưng hàm so sánh lúc này dùng memcmp(pool + start, pool + other.start, len). memcmp được tối ưu về mặt assembly với các thanh ghi SIMD, so sánh nhiều byte song song trong một lần. Kết quả thực tế cho thấy lợi ích từ cache hit tốt và SIMD bù đắp hoàn toàn cho phần phức tạp thuật toán tăng thêm — thời gian chạy thực tế của lần 2 vượt hẳn lần 1.
