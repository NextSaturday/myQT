#pragma once

#include <QtWidgets/QWidget>
#include "ui_tSelection.h"

#include <QTableView>
#include <QTableWidget>
#include <QPushButton>
#include <QStandardItemModel>

class tSelection : public QWidget
{
    Q_OBJECT

public:
    tSelection(QWidget *parent = Q_NULLPTR);

private:
    Ui::tSelectionClass ui;

public slots:
	void selectAll();

private:
	QTableView * m_tableView;
	QStandardItemModel * m_tableModel;

	QPushButton * m_buttonSelect;

private:
	void loadData();
};
