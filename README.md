# HCMUS-DSA-Project-Sorting-Benchmark

Báo cáo đồ án 1: Sorting benchmark
Thông tin chung
Tên môn học: Cấu trúc dữ liệu và Giải thuật
Thời gian: Học kỳ II, năm học 2025 - 2026
Sinh viên: Nguyễn Lê Chí Tường - MSSV: 25120465
Lớp: 25CTT6 - Khoa CNTT - HCMUS

Benchmark 1
Ở lần chạy đầu tiên, tôi chọn Heap Sort tự cài đặt cho cả 3 bài.

Lý do khá thực dụng: đồ án này chấm điểm dựa trên test case do các bạn khác viết để triệt hạ nhau. Nếu dùng Quick Sort, chỉ cần một test case xấu (ví dụ mảng xếp ngược hoặc toàn số trùng nhau) là thuật toán kẹt ở O(N^2) ngay. Heap Sort an toàn hơn. Dù dữ liệu có tệ cỡ nào thì nó vẫn giải quyết gọn trong O(N log N). Ngoài ra, thuật toán này không cần xin thêm RAM của hệ thống, giúp tôi loại được nguy cơ bị sập do quá giới hạn bộ nhớ.

Cách sinh test case (test_gen.cpp)
Thay vì random dữ liệu bình thường, tôi nhắm vào các lỗi phổ biến mà sinh viên hay mắc phải khi tự code.

Với mảng số nguyên, tôi tạo một mảng xếp giảm dần để ép các bản cài đặt Quick Sort cơ bản chạy lố thời gian. Tôi cũng làm một test lặp lại đúng 2 con số để kiểm tra xem thuật toán phân hoạch mảng có bị lệch không. Hiểm nhất là test đan xen số lớn nhất và nhỏ nhất của kiểu int 32-bit. Nhiều người quen tay viết hàm so sánh bằng phép trừ (a - b). Khi gặp test này, máy sẽ bị tràn số và chấm sai kết quả.

Với dữ liệu chuỗi, điểm yếu lớn nhất là chi phí đi so sánh từng chữ cái. Tôi sinh ra các chuỗi dài 100 ký tự, trong đó 99 ký tự đầu giống hệt nhau. Thuật toán của các bài nộp khác sẽ phải lặp qua 99 ký tự đó nhiều lần vô ích chỉ để đối chiếu đúng một ký tự cuối cùng. Ở bài C, tôi gài thêm test có chuỗi ngắn nằm ngay đầu chuỗi dài để làm khó các hàm so sánh tự chế.

Benchmark 2
Sang lần chạy hai, tôi đổi chiến thuật để bào thời gian chạy xuống mức thấp nhất.

Ở bài A, tôi chuyển sang Radix Sort cơ số 256. Thuật toán này không dùng phép so sánh mà xếp số theo từng byte nên tốc độ lướt qua mảng nhanh hơn hẳn. Vì Radix Sort thao tác trên bit nên nó không chạy được với số âm. Để lách luật, tôi cộng thêm 2^31 vào đầu vào để chuyển hết về số dương, sắp xếp xong thì trừ đi để trả về dữ liệu gốc.

Sang bài B, các chuỗi dài 100 ký tự bắt đầu gây áp lực lên bộ nhớ. Nếu gọi hàm swap đổi chỗ liên tục, chương trình sẽ rất chậm. Tôi quyết định giữ các chuỗi nằm im một chỗ, tạo thêm một mảng phụ lưu index của chúng, rồi đem Merge Sort đi sắp xếp cái mảng index này. Cách này không bắt máy tính phải chép qua chép lại dữ liệu chuỗi.

Riêng bài C có giới hạn 1 giây rất gắt. Nếu cứ liên tục gọi hàm đếm chiều dài chuỗi thì chắc chắn sẽ bị quá giờ. Tôi dùng kỹ thuật chia rổ (Bucket Sort). Tôi tạo sẵn 205 mảng rỗng; đọc được chuỗi dài bao nhiêu thì thả ngay vào rổ đó. Cách này giúp tôi gom nhóm chiều dài xong xuôi mà không cần tốn một phép so sánh nào. Việc còn lại chỉ là chạy Merge Sort nội bộ cho từng rổ. Để tránh việc đệ quy xin RAM liên tục làm chậm máy, tôi dọn sẵn một mảng tạm dùng chung và cấp phát đúng một lần từ lúc chạy main.
