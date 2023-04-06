#include "tSelection.h"
#include <QFile>
#include <QVBoxLayout>
#include <iostream>

tSelection::tSelection(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	this->resize(1000, 1000);

	QFont textFont;
	textFont.setPointSize(12);
	textFont.setFamily("Microsoft YaHei");

	m_buttonSelect = new QPushButton("Select All", this);
	m_buttonSelect->setFixedHeight(50);
	connect(m_buttonSelect, &QPushButton::clicked, this, &tSelection::selectAll);

	m_tableView = new QTableView(this);
	m_tableModel = new QStandardItemModel;

	//m_tableView->setFont(textFont);
	m_tableView->setModel(m_tableModel);
	m_tableView->setWordWrap(false);
	m_tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
	m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

	QVBoxLayout *mainLayout = new QVBoxLayout(this);
	mainLayout->addWidget(m_tableView);
	mainLayout->addWidget(m_buttonSelect);
	this->setLayout(mainLayout);

	loadData();
}

void tSelection::loadData()
{
	static const char* DefQSReceiverInfoTableSize[20][3] =
	{
		{"ID" , "130", "0"},
		{"Line" , "110", "0"},
		{"Point" , "110", "0"},
		{"Index" , "60", "0"},
		{"Type" , "60", "0"},
		{"X" , "120", "0"},
		{"Y" , "120", "0"},
		{"Z" , "120", "0"},
		{"Lat.-084" , "180", "0"},
		{"Long.-084" , "180", "0"},
		{"Elav.-84" , "180", "0"},
		{"Status" , "100", "0"},
		{"Point Depth" , "120", "0"},
		{"Water Depth" , "120", "0"},
		{"Seis Datum" , "150", "0"},
		{" " , "150", "0"},
		{" " , "150", "0"},
		{" " , "150", "0"},
		{" " , "150", "0"}
	};

	m_tableModel->setColumnCount(11);
	for (int i = 0; i < 11; i++)
	{
		m_tableModel->setHeaderData(i, Qt::Horizontal, QString::fromLocal8Bit(DefQSReceiverInfoTableSize[i][0]));
	}

	const int rowCount = 10000;
	m_tableModel->setRowCount(rowCount);

	for (int i = 0; i < rowCount; ++i)	
	{
		m_tableModel->setData(m_tableModel->index(i, 0), i);
		m_tableModel->setData(m_tableModel->index(i, 1), i);
		m_tableModel->setData(m_tableModel->index(i, 2), i);
		m_tableModel->setData(m_tableModel->index(i, 3), i);
		m_tableModel->setData(m_tableModel->index(i, 4), i);
		m_tableModel->setData(m_tableModel->index(i, 5), i);
		m_tableModel->setData(m_tableModel->index(i, 6), i);
		m_tableModel->setData(m_tableModel->index(i, 7), i);
		m_tableModel->setData(m_tableModel->index(i, 8), i);
		m_tableModel->setData(m_tableModel->index(i, 9), i);
		m_tableModel->setData(m_tableModel->index(i, 10), i);
	}
}

void tSelection::selectAll()
{
	m_tableView->clearSelection();

	const int rowCount = m_tableModel->rowCount();
	const int columnCount = m_tableModel->columnCount();
	QItemSelectionModel * sm = m_tableView->selectionModel();

	// METHOD 1 : this code will lead to lag
	QItemSelection selection;
	for (int i = 0; i < rowCount; ++i)
	{
		QModelIndex left = m_tableModel->index(i, 0);
		QModelIndex right = m_tableModel->index(i, columnCount - 1);
		selection.merge(QItemSelection(left, right), QItemSelectionModel::Select);
	}
	sm->select(selection, QItemSelectionModel::Select);

	// METHOD 2 : this code will lead to lag
	//for (int i = 0; i < rowCount; ++i)
	//{
	//	QItemSelection selection(m_tableModel->index(i, 0), m_tableModel->index(i, columnCount - 1));
	//	sm->select(selection, QItemSelectionModel::Select);
	//}

	//// METHOD 3 : this code works as well as Ctrl + A
	//QItemSelection selection(m_tableModel->index(0, 0), m_tableModel->index(rowCount - 1, columnCount - 1));
	//sm->select(selection, QItemSelectionModel::Select);

	//// METHOD 4 : this code works as well as Ctrl + A
	//QItemSelection selection;
	//selection.merge(QItemSelection(m_tableModel->index(0, 0), m_tableModel->index(rowCount - 1, columnCount - 1)), QItemSelectionModel::Select);
	//sm->select(selection, QItemSelectionModel::Select);
}