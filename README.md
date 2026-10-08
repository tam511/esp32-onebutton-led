# Bài 4: Điều khiển 1 LED bằng OneButton

---

## 1. Sơ đồ kết nối phần cứng (Hardware Setup)

- **Vi điều khiển:** ESP32 Dev Module (DOIT ESP32 DEVKIT V1)
- **LED 1 (Built-in LED):** Chân **GPIO2** (D2)
- **Nút nhấn (External Button):** Chân **GPIO4** (D4) — Cấu hình Active LOW (kết nối với GND, sử dụng trở kéo nội bộ `INPUT_PULLUP`).

---

## 2. Nguyên lý và Logic điều khiển (Software Logic)

Dự án xử lý 3 thao tác nút bấm cơ bản từ thư viện `OneButton`:

1. **Nhấn kép (Double Click):**
   - Nháy LED.
2. **Nhấn đơn (Single Click):**
   - Bật hoặc Tắt (Toggle ON/OFF) LED.

---

# Bài 5: Điều hiển 2 LED

---

## 1. Sơ đồ kết nối phần cứng (Hardware Setup)

- **Vi điều khiển:** ESP32 Dev Module (DOIT ESP32 DEVKIT V1)
- **LED 1 (Built-in LED):** Chân **GPIO2** (D2)
- **LED 2 (Gắn ngoài):** Chân **GPIO19** (D19)
- **Nút nhấn (External Button):** Chân **GPIO4** (D4) — Cấu hình Active LOW (kết nối với GND, sử dụng trở kéo nội bộ `INPUT_PULLUP`).

---

## 2. Nguyên lý và Logic điều khiển (Software Logic)


1. **Nhấn kép (Double Click):**
   - Chuyển đổi đối tượng điều khiển luân phiên giữa **LED 1** và **LED 2**.
2. **Nhấn đơn (Single Click):**
   - Bật hoặc Tắt (Toggle ON/OFF) trạng thái của LED đang được chọn.
3. **Giữ nút (During Long Press):**
   - Kích hoạt chế độ nhấp nháy (Blink) với chu kỳ **200ms** cho LED đang được chọn.
4. **Thả nút (Long Press Stop):**
   - Khôi phục trạng thái Bật/Tắt ban đầu của các LED khi kết thúc thao tác giữ nút.

---
