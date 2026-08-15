/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "clickablelabel.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *_2;
    QHBoxLayout *sourceLayout;
    QLabel *label;
    QLineEdit *sourceLineEdit;
    QPushButton *browseSourceButton;
    QHBoxLayout *destLayout;
    QLabel *label_2;
    QCheckBox *checkBox;
    QLineEdit *destLineEdit;
    QPushButton *browseDestButton;
    QHBoxLayout *qualityLayout;
    QLabel *qualityLabel;
    QSpinBox *qualitySpinBox;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *settingsButton;
    QHBoxLayout *horizontalLayout_2;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QPushButton *startButton;
    QPushButton *stopButton;
    QProgressBar *progressBar;
    QTextEdit *logTextEdit;
    QLabel *statusLabel;
    ClickableLabel *label_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 432);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(600, 0));
        _2 = new QVBoxLayout(centralwidget);
        _2->setObjectName("_2");
        sourceLayout = new QHBoxLayout();
        sourceLayout->setObjectName("sourceLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        sourceLayout->addWidget(label);

        sourceLineEdit = new QLineEdit(centralwidget);
        sourceLineEdit->setObjectName("sourceLineEdit");

        sourceLayout->addWidget(sourceLineEdit);

        browseSourceButton = new QPushButton(centralwidget);
        browseSourceButton->setObjectName("browseSourceButton");
#if QT_CONFIG(whatsthis)
        browseSourceButton->setWhatsThis(QString::fromUtf8(""));
#endif // QT_CONFIG(whatsthis)

        sourceLayout->addWidget(browseSourceButton);


        _2->addLayout(sourceLayout);

        destLayout = new QHBoxLayout();
        destLayout->setObjectName("destLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        destLayout->addWidget(label_2);

        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setChecked(true);

        destLayout->addWidget(checkBox);

        destLineEdit = new QLineEdit(centralwidget);
        destLineEdit->setObjectName("destLineEdit");

        destLayout->addWidget(destLineEdit);

        browseDestButton = new QPushButton(centralwidget);
        browseDestButton->setObjectName("browseDestButton");

        destLayout->addWidget(browseDestButton);


        _2->addLayout(destLayout);

        qualityLayout = new QHBoxLayout();
        qualityLayout->setObjectName("qualityLayout");
        qualityLabel = new QLabel(centralwidget);
        qualityLabel->setObjectName("qualityLabel");

        qualityLayout->addWidget(qualityLabel);

        qualitySpinBox = new QSpinBox(centralwidget);
        qualitySpinBox->setObjectName("qualitySpinBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qualitySpinBox->sizePolicy().hasHeightForWidth());
        qualitySpinBox->setSizePolicy(sizePolicy);
        qualitySpinBox->setMinimumSize(QSize(50, 0));
        qualitySpinBox->setMinimum(1);
        qualitySpinBox->setMaximum(100);
        qualitySpinBox->setValue(100);

        qualityLayout->addWidget(qualitySpinBox);

        horizontalSpacer_2 = new QSpacerItem(5, 5, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        qualityLayout->addItem(horizontalSpacer_2);

        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName("settingsButton");

        qualityLayout->addWidget(settingsButton);


        _2->addLayout(qualityLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 0, 0, 0);

        _2->addLayout(horizontalLayout_2);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);

        _2->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, -1, -1);
        startButton = new QPushButton(centralwidget);
        startButton->setObjectName("startButton");
        startButton->setMouseTracking(false);
        startButton->setAutoFillBackground(false);

        horizontalLayout->addWidget(startButton);

        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName("stopButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stopButton->sizePolicy().hasHeightForWidth());
        stopButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(stopButton);


        _2->addLayout(horizontalLayout);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(0);

        _2->addWidget(progressBar);

        logTextEdit = new QTextEdit(centralwidget);
        logTextEdit->setObjectName("logTextEdit");
        logTextEdit->setReadOnly(true);

        _2->addWidget(logTextEdit);

        statusLabel = new QLabel(centralwidget);
        statusLabel->setObjectName("statusLabel");

        _2->addWidget(statusLabel);

        label_3 = new ClickableLabel(centralwidget);
        label_3->setObjectName("label_3");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMouseTracking(false);
        label_3->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        label_3->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);
        label_3->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        _2->addWidget(label_3, 0, Qt::AlignmentFlag::AlignRight);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "HEIC to JPEG Converter", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Source:", nullptr));
#if QT_CONFIG(tooltip)
        browseSourceButton->setToolTip(QCoreApplication::translate("MainWindow", "<p>Note: If you need to select the entire folder, click Cancel in the first window, then a folder selection window will open.</p>", nullptr));
#endif // QT_CONFIG(tooltip)
        browseSourceButton->setText(QCoreApplication::translate("MainWindow", "Browse...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Destination:", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Use same directory", nullptr));
        browseDestButton->setText(QCoreApplication::translate("MainWindow", "Browse...", nullptr));
        qualityLabel->setText(QCoreApplication::translate("MainWindow", "JPEG Quality:", nullptr));
        settingsButton->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start Conversion", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
