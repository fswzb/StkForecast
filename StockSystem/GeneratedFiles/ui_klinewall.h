/********************************************************************************
** Form generated from reading UI file 'klinewall.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KLINEWALL_H
#define UI_KLINEWALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KLineWallForm
{
public:

    void setupUi(QWidget *KLineWallForm)
    {
        if (KLineWallForm->objectName().isEmpty())
            KLineWallForm->setObjectName(QStringLiteral("KLineWallForm"));
        KLineWallForm->resize(400, 300);

        retranslateUi(KLineWallForm);

        QMetaObject::connectSlotsByName(KLineWallForm);
    } // setupUi

    void retranslateUi(QWidget *KLineWallForm)
    {
        KLineWallForm->setWindowTitle(QApplication::translate("KLineWallForm", "StockForcast", 0));
    } // retranslateUi

};

namespace Ui {
    class KLineWallForm: public Ui_KLineWallForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KLINEWALL_H
