#pragma once

#include <QDialog>

#include "nlohmann/json.hpp"
#include "settings_manager.hpp"

namespace Ui { class EditFanProfileDialog; }

class EditFanProfileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditFanProfileDialog(QWidget* parent = nullptr);
    void set_current_fan_profile_index(unsigned index) noexcept;
    ~EditFanProfileDialog();

signals:
    void current_fan_profile_changed(const nlohmann::json&);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::EditFanProfileDialog* ui;
    unsigned current_fan_profile_index_;
    nlohmann::json app_settings_;

    void showEvent(QShowEvent* event_);
};

