import serial
import threading
import sys
import time

def forward(src, dst, name):
    while True:
        try:
            # Block until at least 1 byte is available, then read all available
            data = src.read(src.in_waiting or 1)
            if data:
                dst.write(data)
                
                # Try to decode as ASCII first
                try:
                    text = data.decode('utf-8')
                    # If it's mostly printable, print as text
                    if any(c.isprintable() for c in text):
                        print(f"{name} [TXT]: {text.strip()}")
                    else:
                        print(f"{name} [HEX]: {data.hex(' ')}")
                except UnicodeDecodeError:
                    # It's binary data (like our 0xA5 frames)
                    print(f"{name} [BIN]: {data.hex(' ')}")
        except Exception as e:
            print(f"\n[FATAL] Stream broken on {name}: {e}")
            break

def main():
    print("==================================================")
    print("  horAIzon 2.0 - Hardware-in-the-loop UART Bridge")
    print("==================================================")
    
    if len(sys.argv) != 4:
        print("Usage: python serial_bridge.py <COM_A> <COM_B> <BAUD>")
        print("Example: python serial_bridge.py COM3 COM11 115200")
        sys.exit(1)
        
    port_a = sys.argv[1]
    port_b = sys.argv[2]
    baud = int(sys.argv[3])
    
    print(f"[*] Attempting to bind {port_a} and {port_b} at {baud} baud...")
    
    try:
        # We use a small timeout so the thread can yield/exit cleanly if needed
        ser_a = serial.Serial(port_a, baud, timeout=0.05, write_timeout=0.05)
        ser_b = serial.Serial(port_b, baud, timeout=0.05, write_timeout=0.05)
    except Exception as e:
        print(f"[ERROR] Failed to acquire lock on COM ports. Are they open in another terminal/monitor?")
        print(f"Exception: {e}")
        sys.exit(1)
        
    print(f"[SUCCESS] Cross-routing active.")
    print("[*] Press Ctrl+C to terminate.")
    
    t1 = threading.Thread(target=forward, args=(ser_a, ser_b, f"{port_a} -> {port_b}"), daemon=True)
    t2 = threading.Thread(target=forward, args=(ser_b, ser_a, f"{port_b} -> {port_a}"), daemon=True)
    
    t1.start()
    t2.start()
    
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\n[*] Terminating bridge and releasing COM locks...")
        ser_a.close()
        ser_b.close()
        sys.exit(0)

if __name__ == "__main__":
    main()
