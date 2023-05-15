#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Namelabel->setVisible(false);
    ui->NameLE->setVisible(false);
    ui->SKULabel->setVisible(false);
    ui->SKULE->setVisible(false);
    ui->QuantityLabel->setVisible(false);
    ui->QuantityLE->setVisible(false);
    ui->PriceLabel->setVisible(false);
    ui->PriceLineEdit->setVisible(false);
    ui->Grocery->setVisible(false);
    ui->Clothing->setVisible(false);
    ui->AddPB->setVisible(false);
    ui->RemovePB->setVisible(false);
    ui->SavePB->setVisible(false);
    ui->LoadPB->setVisible(false);
    ui->SellPB->setVisible(false);
    ui->spinBox->setVisible(false);


    //    if (ui->OptionCB->currentIndex() == 0  )
    //    {
    //        ui->Grocery->setVisible(true);
    //        ui->Clothing->setVisible(false);
    //        ui->InventoryTW->setVisible(true);
    //        ui->InventoryTW_2->setVisible(false);
    //        statusBar = new QStatusBar(this);
    //        setStatusBar(statusBar);
    //    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_OptionCB_currentIndexChanged(int index)
{
    if (ui->OptionCB->currentIndex() == 0)
    {
        ui->Grocery->setVisible(true);
        ui->Clothing->setVisible(false);
        ui->InventoryTW->setVisible(true);
        ui->InventoryTW_2->setVisible(false);
    }
    else
    {
        ui->Grocery->setVisible(false);
        ui->Clothing->setVisible(true);
        ui->InventoryTW->setVisible(false);
        ui->InventoryTW_2->setVisible(true);
    }
}

void MainWindow::on_AddPB_clicked()
{
    string SKU = ui->SKULE->text().toStdString();
    string name = ui->NameLE->text().toStdString();
    int quantity = ui->QuantityLE->text().toInt();
    int price = ui->PriceLineEdit->text().toInt();

    // Check if all fields are filled
    if (!ui->SKULE->text().isEmpty() && !ui->NameLE->text().isEmpty() && !ui->QuantityLE->text().isEmpty() && !ui->PriceLineEdit->text().isEmpty())
    {
        // Check if the SKU is unique
        if (inventory.is_sku_unique(SKU))
        {
            if (ui->OptionCB->currentIndex() == 0)
            {
                string category = ui->CategoryCB->currentText().toStdString();
                Grocery *gItem = new Grocery(name, SKU, quantity, price, category);
                inventory.add_item(gItem);

                // Add to table Widget;
                int row = ui->InventoryTW->rowCount();
                ui->InventoryTW->insertRow(row);

                // adding data to table
                ui->InventoryTW->setItem(row, 0, new QTableWidgetItem(ui->SKULE->text()));
                ui->InventoryTW->setItem(row, 1, new QTableWidgetItem(ui->NameLE->text()));
                ui->InventoryTW->setItem(row, 2, new QTableWidgetItem(ui->QuantityLE->text()));
                ui->InventoryTW->setItem(row, 3, new QTableWidgetItem(ui->PriceLineEdit->text()));
                ui->InventoryTW->setItem(row, 4, new QTableWidgetItem(ui->CategoryCB->currentText()));
            }
            else
            {
                // Add items to the inventory
                string size = ui->SizeCB->currentText().toStdString();
                string color = ui->ColorCB->currentText().toStdString();
                string material = ui->MaterialCB->currentText().toStdString();

                Clothing *cItem = new Clothing(name, SKU, quantity, price, size, color, material);
                inventory.add_item(cItem);

                int row = ui->InventoryTW_2->rowCount();
                ui->InventoryTW_2->insertRow(row);

                // adding data to table
                ui->InventoryTW_2->setItem(row, 0, new QTableWidgetItem(ui->SKULE->text()));
                ui->InventoryTW_2->setItem(row, 1, new QTableWidgetItem(ui->NameLE->text()));
                ui->InventoryTW_2->setItem(row, 2, new QTableWidgetItem(ui->QuantityLE->text()));
                ui->InventoryTW_2->setItem(row, 3, new QTableWidgetItem(ui->PriceLineEdit->text()));
                ui->InventoryTW_2->setItem(row, 4, new QTableWidgetItem(ui->SizeCB->currentText()));
                ui->InventoryTW_2->setItem(row, 5, new QTableWidgetItem(ui->ColorCB->currentText()));
                ui->InventoryTW_2->setItem(row, 6, new QTableWidgetItem(ui->MaterialCB->currentText()));
            }

            // Save inventory to file
            saveInventoryToFile("inventory.txt");
        }
        else
        {
            QString errorMessage = "SKU must be unique";
            statusBar->showMessage(errorMessage, 5000); // Show the error message for 5 seconds
        }
    }
    else
    {
        QString errorMessage = "Fill all blanks";
        statusBar->showMessage(errorMessage, 5000); // Show the error message for 5 seconds
    }
}

void MainWindow::on_RemovePB_clicked()
{
    if (ui->OptionCB->currentIndex() == 0)
    {
        foreach (QTableWidgetItem *item, ui->InventoryTW->selectedItems())
        {
            int row = item->row();
            ui->InventoryTW->removeRow(row);
        }
    }
    else
    {
        foreach (QTableWidgetItem *item, ui->InventoryTW_2->selectedItems())
        {
            int row = item->row();
            ui->InventoryTW_2->removeRow(row);
        }
    }

    // Save inventory to file
    saveInventoryToFile("inventory.txt");
}

void MainWindow::saveInventoryToFile(const string &filename)
{
    ofstream file(filename);
    if (file.is_open())
    {
        for (int i = 0; i < ui->InventoryTW->rowCount(); ++i)
        {
            string sku = ui->InventoryTW->item(i, 0)->text().toStdString();
            string name = ui->InventoryTW->item(i, 1)->text().toStdString();
            int quantity = ui->InventoryTW->item(i, 2)->text().toInt();
            int price = ui->InventoryTW->item(i, 3)->text().toInt();
            string category = ui->InventoryTW->item(i, 4)->text().toStdString();
            file << sku << "," << name << "," << quantity << "," << price << "," << category << endl;
        }

        for (int i = 0; i < ui->InventoryTW_2->rowCount(); ++i)
        {
            string sku = ui->InventoryTW_2->item(i, 0)->text().toStdString();
            string name = ui->InventoryTW_2->item(i, 1)->text().toStdString();
            int quantity = ui->InventoryTW_2->item(i, 2)->text().toInt();
            int price = ui->InventoryTW_2->item(i, 3)->text().toInt();
            string size = ui->InventoryTW_2->item(i, 4)->text().toStdString();
            string color = ui->InventoryTW_2->item(i, 5)->text().toStdString();
            string material = ui->InventoryTW_2->item(i, 6)->text().toStdString();
            file << sku << "," << name << "," << quantity << "," << price << "," << size << "," << color << "," << material << endl;
        }

        file.close();
        qDebug() << "Inventory saved to file: " << QString::fromStdString(filename);
    }
    else
    {
        QString errorMessage = "Error opening file: " + QString::fromStdString(filename);
        statusBar->showMessage(errorMessage, 5000); // Show the error message for 5 seconds
        qDebug() << errorMessage;
        qDebug() << "Error opening file: " << QString::fromStdString(filename);
    }
}

void MainWindow::loadInventoryFromFile(const string &filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            vector<string> tokens;
            stringstream ss(line);
            string token;
            while (getline(ss, token, ','))
            {
                tokens.push_back(token);
            }

            if (tokens.size() == 5)
            {
                string sku = tokens[0];
                string name = tokens[1];
                int quantity = stoi(tokens[2]);
                int price = stoi(tokens[3]);
                string category = tokens[4];
                Grocery *gItem = new Grocery(name, sku, quantity, price, category);
                inventory.add_item(gItem);

                int row = ui->InventoryTW->rowCount();
                ui->InventoryTW->insertRow(row);

                ui->InventoryTW->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(sku)));
                ui->InventoryTW->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(name)));
                ui->InventoryTW->setItem(row, 2, new QTableWidgetItem(QString::number(quantity)));
                ui->InventoryTW->setItem(row, 3, new QTableWidgetItem(QString::number(price)));
                ui->InventoryTW->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(category)));
            }
            else if (tokens.size() == 7)
            {
                string sku = tokens[0];
                string name = tokens[1];
                int quantity = stoi(tokens[2]);
                int price = stoi(tokens[3]);
                string size = tokens[4];
                string color = tokens[5];
                string material = tokens[6];
                Clothing *cItem = new Clothing(name, sku, quantity, price, size, color, material);
                inventory.add_item(cItem);

                int row = ui->InventoryTW_2->rowCount();
                ui->InventoryTW_2->insertRow(row);

                ui->InventoryTW_2->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(sku)));
                ui->InventoryTW_2->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(name)));
                ui->InventoryTW_2->setItem(row, 2, new QTableWidgetItem(QString::number(quantity)));
                ui->InventoryTW_2->setItem(row, 3, new QTableWidgetItem(QString::number(price)));
                ui->InventoryTW_2->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(size)));
                ui->InventoryTW_2->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(color)));
                ui->InventoryTW_2->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(material)));
            }
        }

        file.close();
        qDebug() << "Inventory loaded from file: " << QString::fromStdString(filename);
    }
    else
    {
        QString errorMessage = "Error opening file: " + QString::fromStdString(filename);
        statusBar->showMessage(errorMessage, 5000); // Show the error message for 5 seconds
        qDebug() << errorMessage;
        qDebug() << "Error opening file: " << QString::fromStdString(filename);
    }
}



void MainWindow::on_LoadPB_clicked()
{

    loadInventoryFromFile("inventory.txt");
}


void MainWindow::on_SavePB_clicked()
{
    saveInventoryToFile("inventory.txt");
}


void MainWindow::on_loginManagerPB_clicked()
{
    ui->Namelabel->setVisible(true);
    ui->NameLE->setVisible(true);
    ui->SKULabel->setVisible(true);
    ui->SKULE->setVisible(true);
    ui->QuantityLabel->setVisible(true);
    ui->QuantityLE->setVisible(true);
    ui->PriceLabel->setVisible(true);
    ui->PriceLineEdit->setVisible(true);
    ui->Grocery->setVisible(true);
    ui->Clothing->setVisible(true);
    ui->AddPB->setVisible(true);
    ui->RemovePB->setVisible(true);
    ui->SavePB->setVisible(true);
    ui->LoadPB->setVisible(true);
    ui->SellPB->setVisible(false);
    ui->spinBox->setVisible(false);

    if (ui->OptionCB->currentIndex() == 0  )
    {
        ui->Grocery->setVisible(true);
        ui->Clothing->setVisible(false);
        ui->InventoryTW->setVisible(true);
        ui->InventoryTW_2->setVisible(false);
        statusBar = new QStatusBar(this);
        setStatusBar(statusBar);
    }
}


void MainWindow::on_LoginSalesmanPB_clicked()
{
    ui->Namelabel->setVisible(false);
    ui->NameLE->setVisible(false);
    ui->SKULabel->setVisible(false);
    ui->SKULE->setVisible(false);
    ui->QuantityLabel->setVisible(false);
    ui->QuantityLE->setVisible(false);
    ui->PriceLabel->setVisible(false);
    ui->PriceLineEdit->setVisible(false);
    ui->Grocery->setVisible(false);
    ui->Clothing->setVisible(false);
    ui->AddPB->setVisible(false);
    ui->RemovePB->setVisible(false);
    ui->SavePB->setVisible(false);
    ui->LoadPB->setVisible(false);
    ui->SellPB->setVisible(true);
    ui->spinBox->setVisible(true);
}


void MainWindow::on_SellPB_clicked()
{
    // Get the selected item
    if (ui->OptionCB->currentIndex() == 0)
    {
        QList<QTableWidgetItem *> selectedItems = ui->InventoryTW->selectedItems();
        if (selectedItems.isEmpty())
        {
            // write the error msg in status bar in future
            return;
        }

        QTableWidgetItem *item = selectedItems.at(0);
        int row = item->row();

        QTableWidgetItem *quantityItem = ui->InventoryTW->item(row, 2);

        QString quantity = quantityItem->text();
        QString amount = ui->spinBox->text();

        //    bool ok = false;
        //    int soldQuantity = QInputDialog::getInt(this, tr("Sell Item"), tr("Enter sold quantity:"), 1, 1, quantity.toInt(), 1, &ok);
        //    if (!ok)
        //        return;

        // Update quantity in the table
        int newQuantity = quantity.toInt() - amount.toInt();
        quantityItem->setText(QString::number(newQuantity));
    }
    else
    {
        QList<QTableWidgetItem *> selectedItems = ui->InventoryTW_2->selectedItems();
        if (selectedItems.isEmpty())
        {
            // write the error msg in status bar in future
            return;
        }

        QTableWidgetItem *item = selectedItems.at(0);
        int row = item->row();

        QTableWidgetItem *quantityItem = ui->InventoryTW_2->item(row, 2);

        QString quantity = quantityItem->text();
        QString amount = ui->spinBox->text();

        //    bool ok = false;
        //    int soldQuantity = QInputDialog::getInt(this, tr("Sell Item"), tr("Enter sold quantity:"), 1, 1, quantity.toInt(), 1, &ok);
        //    if (!ok)
        //        return;

        // Update quantity in the table
        int newQuantity = quantity.toInt() - amount.toInt();
        quantityItem->setText(QString::number(newQuantity));
    }
}

