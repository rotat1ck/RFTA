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

void MainWindow::uploadFile(const QString &filePath) {
    // Create a network access manager
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    // Create a request to the server
    QUrl url("http://localhost:5000/upload"); // Change to your server URL
    QNetworkRequest request(url);

    // Prepare the file for upload
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Could not open file for reading:" << filePath;
        return;
    }

    // Create a multipart form data
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/octet-stream"));
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + QFileInfo(file).fileName() + "\""));
    filePart.setBody(file.readAll());
    multiPart->append(filePart);

    // Send the request
    QNetworkReply *reply = manager->post(request, multiPart);
    multiPart->setParent(reply); // Delete the multiPart with the reply

    // Connect to the reply's finished signal
    connect(reply, &QNetworkReply::finished, [reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "File uploaded successfully:" << reply->readAll();
        } else {
            qDebug() << "Error uploading file:" << reply->errorString();
        }
        reply->deleteLater();
    });
}

void MainWindow::on_chooseFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Select a file to upload");
        if (!filePath.isEmpty()) {
            uploadFile(filePath);
        } else {
            qDebug() << "No file selected.";
        }
}

