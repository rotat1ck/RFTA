#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::uploadFile(const QString &filePath, QUrl &url) {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    QNetworkRequest request(url);

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading:" << filePath;
        return;
    }

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + QFileInfo(file).fileName() + "\""));
    filePart.setBody(file.readAll());
    multiPart->append(filePart);

    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply);


    connect(reply, &QNetworkReply::finished, [reply, this]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "File uploaded successfully:" << reply->readAll();
            ui->fileLoadingBar->setValue(100);
        } else {
            qDebug() << "Error uploading file:" << reply->errorString();
        }
        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::uploadProgress, this, &MainWindow::updateProgress);
}

void MainWindow::updateProgress(qint64 bytesSent, qint64 bytesTotal) {
    if (bytesTotal > 0) {
        int progress = static_cast<int>((bytesSent * 100) / bytesTotal);
        ui->fileLoadingBar->setValue(progress); // Update the progress bar
    }
}

void MainWindow::on_chooseFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select a file to upload");
        if (!filePath.isEmpty()) {
            ui->fileLoadingBar->setValue(0);
            QUrl url(ui->lineEdit->text());
            if (!url.isEmpty()) {
                uploadFile(filePath, url);
            } else {
                QUrl url("http://192.168.0.14:7777/upload");
                uploadFile(filePath, url);
            }
        } else {
            qDebug() << "No file selected.";
        }
}

