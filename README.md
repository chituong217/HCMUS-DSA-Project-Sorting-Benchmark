# Báo cáo đồ án 1: Sorting benchmark

## Thông tin chung
Tên môn học: Cấu trúc dữ liệu và Giải thuật
Thời gian: Học kỳ II, năm học 2025 - 2026
Nhóm sinh viên thực hiện (Lớp 25CTT6):
- Nguyễn Lê Chí Tường (MSSV: 25120465)
- Đoàn Hoàng Việt (MSSV: 25120469)
- Lê Dương Hồng Quân (MSSV: 25120424)

## Benchmark 1: Lựa chọn thuật toán
Ở lần chạy đầu tiên, nhóm quyết định dùng Quick Sort cho bài A và B, còn bài C thì dùng Merge Sort. 

Với dữ liệu số nguyên và chuỗi thông thường, Quick Sort là lựa chọn tốt vì nó không tốn thêm bộ nhớ in-place và tận dụng bộ đệm cache cực kỳ hiệu quả. Thời gian chạy trung bình O(N log N) là đủ để vượt qua các test cơ bản. Tuy nhiên, Quick Sort có một điểm yếu chết người là dễ bị trượt xuống O(N^2) nếu gặp dữ liệu xấu. Bài C có thời gian giới hạn gắt hơn và phải so sánh qua hai nấc là chiều dài và từ điển, nên nhóm dùng Merge Sort để đảm bảo an toàn. Merge Sort lúc nào cũng giữ vững tốc độ O(N log N) bất chấp việc mảng có bị xếp ngược hay chứa nhiều phần tử trùng lặp.

## Cách sinh test case (test_gen.cpp)
Mục tiêu của bộ test này không phải là sinh dữ liệu ngẫu nhiên, mà là đánh sập các thuật toán Quick Sort dùng chốt pivot cố định và các hàm so sánh tự chế của những nhóm khác trong lớp.

Với bài số nguyên, nhóm tạo một mảng xếp giảm dần để ép các cài đặt Quick Sort lặp đủ N tầng đệ quy, đẩy thời gian chạy lên tối đa. Nhóm cũng thiết kế một test chỉ đan xen đúng hai số 1 và 2 để làm rối loạn các hàm partition. Bẫy hiểm nhất là test thứ 5, chỉ in ra số lớn nhất 2147483647 và nhỏ nhất -2147483648 của kiểu int 32-bit. Rất nhiều người quen tay viết hàm so sánh bằng phép trừ a trừ b. Khi gặp test này, máy tính sẽ bị tràn bộ nhớ và cho ra kết quả sai hoàn toàn.

Với mảng chuỗi, phép so sánh từng chữ cái là nơi dễ bị nghẽn nhất. Nhóm sinh ra các chuỗi dài 100 ký tự có 99 chữ cái đầu giống hệt nhau. Máy tính của các nhóm sẽ phải lặp qua 99 chữ cái đó vô ích chỉ để thấy sự khác biệt ở ký tự cuối cùng. Riêng ở bài C, nhóm lồng ghép một chuỗi ngắn làm tiền tố cho một chuỗi dài để ép thuật toán phải duyệt hết độ dài chuỗi ngắn mới phát hiện ra điểm khác biệt.

## Benchmark 2: Tối ưu thuật toán
Sang lần chạy hai, nhóm bỏ các thư viện có sẵn để tự tối ưu sâu hơn nhằm bào thời gian chạy xuống mức thấp nhất.

Ở bài số nguyên A, nhóm chuyển sang Radix Sort. Thuật toán này không dùng phép so sánh mà chia số theo từng byte để xếp, giúp tốc độ lướt qua mảng nhanh hơn O(N log N) rất nhiều. Vì Radix Sort thao tác trực tiếp trên bit nên nó không hiểu số âm. Để lách luật, nhóm cộng thêm 2^31 vào toàn bộ đầu vào để chuyển chúng thành số dương, sắp xếp xong thì trừ đi lượng đó để trả về dữ liệu gốc.

Sang bài chuỗi từ điển B, việc hoán vị các chuỗi dài bằng Quick Sort quá tốn tài nguyên. Nhóm dùng MSD Radix Sort. Thay vì đem hai chuỗi ra so sánh, thuật toán sẽ chia các chuỗi vào 26 nhóm dựa trên chữ cái đầu tiên, sau đó đệ quy chia tiếp cho chữ cái thứ hai. Kỹ thuật này triệt tiêu hoàn toàn thao tác gọi hàm so sánh chuỗi phức tạp.

Riêng bài C, nhóm lôi kỹ thuật BucketSort ra xài. Cụ thể, nhóm tạo sẵn các mảng rỗng tương ứng với chiều dài từ 10 đến 100. Đọc được chuỗi dài bao nhiêu thì thả ngay vào rổ bấy nhiêu. Bước này giúp gom nhóm chiều dài xong xuôi ngay từ lúc đọc input mà không tốn một phép so sánh nào. Sau đó, nhóm chỉ cần chạy Merge Sort nội bộ cho từng rổ để sắp xếp theo thứ tự từ điển là xong.
