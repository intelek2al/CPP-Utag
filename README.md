# Utag
___

 ### Description:
 Ucode project: utag - app to read and write tags of mp3 files in c++ 
 ### Developers:
 [Mykyta Savytskyi](https://github.com/intelek2al) | 
 [Serhiy Nikolayenko](https://github.com/N-911) | 
 

###Screenshots 
![imagename](TargetUrl)

###Tech/framework used

#### 1.Built with

    cmake

#### 2.GUI library

    Qt

#### 3. External Libraries

    taglib

 ###Installation:
 1. git clone --recursive https://github.com/intelek2al/CPP-Utag
 2. cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build
 
 ###How to use?
 
 ./build/app/utag [directory]
 
 ###Code
 
 ```c++
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString path = "~/", QWidget *parent = nullptr);
    ~MainWindow() override;

 ```
 ###Features:

###Shortcuts

*Save: Cmd + S

*Quit: Cmd + Q

### License
[MIT](https://choosealicense.com/licenses/mit/)

---

https://medium.com/@saumya.ranjan/how-to-write-a-readme-md-file-markdown-file-20cb7cbcd6f

https://developer.apple.com/design/human-interface-guidelines/macos/overview/themes/
