#ifndef TXT2JSON_H
#define TXT2JSON_H

#include <QMainWindow>

namespace Ui {
class txt2json;
}

class txt2json : public QMainWindow
{
    Q_OBJECT

public:
    explicit txt2json(QWidget *parent = 0);
    ~txt2json();

private:
    Ui::txt2json *ui;

public slots:
    generate();
};

#endif // TXT2JSON_H
