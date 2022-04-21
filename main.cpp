#include <QApplication>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QSlider>
#include <QVBoxLayout>

class Circle : public QWidget
{
public:
    explicit Circle(QWidget* parent = Q_NULLPTR)
            : QWidget(parent), color(Qt::green)
    {
        setFixedSize(200, 200);
    }

    void setColor(QColor col)
    {
        color = col;
    }

protected:
    virtual void paintEvent(QPaintEvent* event) override
    {
        QPainter painter(this);
        painter.setBrush(QBrush(color, Qt::SolidPattern));
        painter.drawEllipse(5, 10, 170, 170);
    }

private:
    QColor color;
};

class DiscoCircle : public QWidget
{
    Q_OBJECT

public:
    explicit DiscoCircle(QWidget* parent = Q_NULLPTR)
            : QWidget(parent)
    {
        setFixedSize(200, 250);

        auto* slider = new QSlider(Qt::Horizontal);
        slider->setMinimum(0);
        slider->setMaximum(100);

        auto* circle = new Circle;

        setLayout(new QVBoxLayout);
        layout()->addWidget(circle);
        layout()->addWidget(slider);

        connect(slider, &QSlider::valueChanged, this,[circle, this](int newValue)
        {
            QColor color;

            if(newValue <= 33)
                color = Qt::green;

            else if(newValue <= 66)
                color = Qt::yellow;

            else color = Qt::red;

            circle->setColor(color);
            circle->update();
        });
    }

protected:
    virtual QSize minimumSizeHint() const override
    {
        return QSize(100, 100);
    }
};

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DiscoCircle circ;
    circ.show();

    return QApplication::exec();
}

#include "main.moc"