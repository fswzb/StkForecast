#ifndef  TOOL_BAR_SFDDS32SDFDS_H_
#define  TOOL_BAR_SFDDS32SDFDS_H_


#include <QtWidgets/QWidget>

class QLabel;
class QPushButton;
class QToolButton;

class ToolBar : public QWidget
{
    Q_OBJECT

public:

    explicit ToolBar(QWidget *parent = 0);
    ~ToolBar(){}

protected:

    // ˫�����������н�������/��ԭ
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override; 

    // �����������϶�
    virtual void mousePressEvent(QMouseEvent *event) override;

    // ���ý��������ͼ��
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
     
    void onClicked();

private:
     
    //void updateMaximize();

private:

    //QLabel *m_pIconLabel;
    //QLabel *m_pTitleLabel;

    QPushButton *m_pABPen;
    QToolButton *m_pClearPen;

    //QPushButton *m_pMaximizeButton;
    //QPushButton *m_pCloseButton;
};

#endif // TOOL_BAR_SFDDS32SDFDS_H_