# 🖩 Leon's Simple Calculator

Leon’s Simple Calculator is a **Windows-based GUI calculator** built using **C++ and Win32 API**. It supports **basic arithmetic operations** and features **a resizable, fullscreen-friendly UI** with scalable fonts.  

![image](https://github.com/user-attachments/assets/73103538-fff3-46dc-9b14-55c65bb67dcc)
![image](https://github.com/user-attachments/assets/298ceab1-7940-41bf-a01c-4a7789921d54)


---

## 🚀 **Features**
✔ **Basic Arithmetic:** Supports `+`, `-`, `*`, `/` operations.  
✔ **Resizable UI:** Fully adjusts to different window sizes, including fullscreen.  
✔ **Scalable Fonts:** Button and output text dynamically scale for better readability.  
✔ **Keyboard Shortcuts:** Press `F11` to toggle fullscreen.  
✔ **Minimalist UI:** Clean and simple interface for easy usage.  

---

## 📥 **Installation**
### **🔹 Windows Users**
1. **Download `Calculator.exe`** from the [latest release](https://github.com/YOUR_GITHUB_USERNAME/YOUR_REPO_NAME/releases).
2. **Run the executable** (`Calculator.exe`).
3. **Start performing calculations!** 🎉  

### **🔹 Compiling from Source**
If you want to build the project yourself:
#### **🔧 Requirements**
- **Windows Subsystem for Linux (WSL)** (or MinGW installed)
- **G++ Compiler for Windows**

#### **💻 Compilation Steps**
```bash
x86_64-w64-mingw32-g++ CalculatorGUI.cpp -o Calculator.exe -mwindows -static-libgcc -static-libstdc++ -static
