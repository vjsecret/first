#ifndef DEMO2_H
#define DEMO2_H
#include <Qwidget>

class QLable;
class QPushButton;
class QCheckBox;
class QRadioButton;
class QlineEdit;

//Demo2Ä~©ÓQwidget
class Demo2:public Qwidget{
    Q_OBJECT
public:
    Demo2(Qwidget *parent=0);
private:
    QLable *b1;
    QPushButton *b2;
    QCheckBox *b3;
    QRadioButton *b4;
    QlineEdit *b5;
};

#endif // DEMO2_H
