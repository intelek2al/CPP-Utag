# Utag
___

 ### Description:
    Ucode project: utag - app to read and write tags of mp3 files in c++ 
 ### Developers:
 [Mykyta Savytskyi](https://github.com/intelek2al) | 
 [Serhiy Nikolayenko](https://github.com/N-911)
 

### Screenshots 
 ![utag main](/app/resources/main_utag.png)

### Tech/framework used

#### 1.Built with

 [CMake](https://cmake.org)

#### 2.GUI library

 [Qt](https://www.qt.io)

#### 3. External Libraries

 [Taglib](https://taglib.org)
   
 ### Installation:
    1. git clone --recursive https://github.com/intelek2al/CPP-Utag
    2. cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build
 
 ### How to use?
    ./build/app/utag [directory]
 
 ### Code
 
 ```c++
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString path = "~/", QWidget *parent = nullptr);
    ~MainWindow() override;

 ```
### Features:

### Shortcuts
* Save: Cmd + S
* Log:  Cmd + L
* Quit: Cmd + Q

### License
[MIT](https://choosealicense.com/licenses/mit/)

---

