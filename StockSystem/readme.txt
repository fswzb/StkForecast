

�����ƶ� https://blog.csdn.net/qq_28093585/article/details/78483019

�Զ��� ������ https://blog.csdn.net/qq_28093585/article/details/78517358

�Զ�������� https://blog.csdn.net/liang19890820/article/details/50555298

����

ͨ���Ͻ����ݣ�����ʵ�����Զ��崰����ƶ�����������ȱ��һ������������ʾ�����ͼ�ꡢ���⣬�Լ����ƴ�����С������󻯡��رյİ�ť��

�Զ�������������еĿؼ����Ƕ����Զ��ƣ����磺�ڱ���������ӻ��������ð�ť�Լ������ؼ���

 
����дͼƬ����

�Զ��������

ʵ��

title_bar.h

#ifndef TITLE_BAR
#define TITLE_BAR

#include <QWidget>

class QLabel;
class QPushButton;

class TitleBar : public QWidget
{
    Q_OBJECT

public:
    explicit TitleBar(QWidget *parent = 0);
    ~TitleBar();

protected:

    // ˫�����������н�������/��ԭ
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

    // �����������϶�
    virtual void mousePressEvent(QMouseEvent *event);

    // ���ý��������ͼ��
    virtual bool eventFilter(QObject *obj, QEvent *event);

private slots:

    // ������С�������/��ԭ���رղ���
    void onClicked();

private:

    // ���/��ԭ
    void updateMaximize();

private:
    QLabel *m_pIconLabel;
    QLabel *m_pTitleLabel;
    QPushButton *m_pMinimizeButton;
    QPushButton *m_pMaximizeButton;
    QPushButton *m_pCloseButton;
};

#endif // TITLE_BAR
 
title_bar.cpp

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include "title_bar.h"

#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent)
    : QWidget(parent)
{
    setFixedHeight(30);

    m_pIconLabel = new QLabel(this);
    m_pTitleLabel = new QLabel(this);
    m_pMinimizeButton = new QPushButton(this);
    m_pMaximizeButton = new QPushButton(this);
    m_pCloseButton = new QPushButton(this);

    m_pIconLabel->setFixedSize(20, 20);
    m_pIconLabel->setScaledContents(true);

    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_pMinimizeButton->setFixedSize(27, 22);
    m_pMaximizeButton->setFixedSize(27, 22);
    m_pCloseButton->setFixedSize(27, 22);

    m_pTitleLabel->setObjectName("whiteLabel");
    m_pMinimizeButton->setObjectName("minimizeButton");
    m_pMaximizeButton->setObjectName("maximizeButton");
    m_pCloseButton->setObjectName("closeButton");

    m_pMinimizeButton->setToolTip("Minimize");
    m_pMaximizeButton->setToolTip("Maximize");
    m_pCloseButton->setToolTip("Close");

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_pIconLabel);
    pLayout->addSpacing(5);
    pLayout->addWidget(m_pTitleLabel);
    pLayout->addWidget(m_pMinimizeButton);
    pLayout->addWidget(m_pMaximizeButton);
    pLayout->addWidget(m_pCloseButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(5, 0, 5, 0);

    setLayout(pLayout);

    connect(m_pMinimizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pMaximizeButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
}

TitleBar::~TitleBar()
{

}

void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit m_pMaximizeButton->clicked();
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
       event->ignore();
#else
#endif
}

bool TitleBar::eventFilter(QObject *obj, QEvent *event)
{
    switch (event->type())
    {
    case QEvent::WindowTitleChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            m_pTitleLabel->setText(pWidget->windowTitle());
            return true;
        }
    }
    case QEvent::WindowIconChange:
    {
        QWidget *pWidget = qobject_cast<QWidget *>(obj);
        if (pWidget)
        {
            QIcon icon = pWidget->windowIcon();
            m_pIconLabel->setPixmap(icon.pixmap(m_pIconLabel->size()));
            return true;
        }
    }
    case QEvent::WindowStateChange:
    case QEvent::Resize:
        updateMaximize();
        return true;
    }
    return QWidget::eventFilter(obj, event);
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        if (pButton == m_pMinimizeButton)
        {
            pWindow->showMinimized();
        }
        else if (pButton == m_pMaximizeButton)
        {
            pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
        }
        else if (pButton == m_pCloseButton)
        {
            pWindow->close();
        }
    }
}

void TitleBar::updateMaximize()
{
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel())
    {
        bool bMaximize = pWindow->isMaximized();
        if (bMaximize)
        {
            m_pMaximizeButton->setToolTip(tr("Restore"));
            m_pMaximizeButton->setProperty("maximizeProperty", "restore");
        }
        else
        {
            m_pMaximizeButton->setProperty("maximizeProperty", "maximize");
            m_pMaximizeButton->setToolTip(tr("Maximize"));
        }

        m_pMaximizeButton->setStyle(QApplication::style());
    }
}
 
�ӿ�˵��

mousePressEvent
֮ǰ�����ǽ������ƶ����¼�д�����������棬�����һ�����⣬һ������£��ǽ������ű��������ƶ����ƶ��������ǽ����е�����λ�ö����Խ����϶����������ǽ��¼�д�ڱ������бȽϺ���

mouseDoubleClickEvent
˫������������д�������/��ԭ������������Ҫ��д���¼����п��ơ�

eventFilter

�¼������������ﱻ�����Ĵ���Ϊ���������ڵĴ��壬���Ե�������⡢ͼ�����Ϣ�����ı�ʱ��������ҲӦ����֮�ı䡣

��ò�Ҫͨ��ֱ�ӵ��ýӿڵ���ʽ��������Ӧ����Ϊ�����磺TitleBar�ж���һ��public������ר���޸ı�����ͼ�꣬��������ɲ���Ҫ���鷳����ΪQt������ǻ����¼��ģ����Դ˴����ù������ķ�ʽ��

updateMaximize

��Ϊ�����С�����仯��ʱ����󻯵�ͼ�ꡢ��ʾӦ�ö�Ӧ�ķ����仯��������eventFilter���¼�����ʱ���á�

ʹ�÷�ʽ

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    TitleBar *pTitleBar = new TitleBar(this);
    installEventFilter(pTitleBar);

    resize(400, 300);
    setWindowTitle("Custom Window");
    setWindowIcon(QIcon(":/Images/logo"));

    QPalette pal(palette());
    pal.setColor(QPalette::Background, QColor(50, 50, 50));
    setAutoFillBackground(true);
    setPalette(pal);

    QVBoxLayout *pLayout = new QVBoxLayout();
    pLayout->addWidget(pTitleBar);
    pLayout->addStretch();
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);
}
 ע��

installEventFilter������setWindowTitle��setWindowIcon֮ǰ���ã���Ϊ�����Ȱ�װ�¼�����������Ӧ�¼�����ʱ���Ż�����������eventFilter�¼��С�