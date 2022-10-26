#pragma once

#include <QDialog>
#include <QProcess>

namespace Ui { class ReportABugDialog; }

class ReportABugDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ReportABugDialog(QWidget* parent = nullptr);
    ~ReportABugDialog();

private slots:
    void on_pushButton_ok_clicked();
    void on_label_text_linkActivated(const QString& link);

private:
    Ui::ReportABugDialog* ui;
    QProcess external_process_;

    void showEvent(QShowEvent* show_event);
};
