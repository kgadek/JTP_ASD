#include <qt4/QtGui/QApplication>
#include <qt4/QtGui/QHBoxLayout>
#include <qt4/QtGui/QVBoxLayout>
#include <qt4/QtGui/QGridLayout>
#include "renderarea.h"

int main(int argc, char **argv) {
    QApplication app(argc,argv);

    QWidget *window = new QWidget;
    window->setWindowTitle("JTP1-6 by Konrad Gadek");

    // Dodanie obszaru rysunkowego ___________________________________________

    RenderArea *ra = new RenderArea();
    ra->setFixedWidth(ra->sizeHint().width());
    ra->setFixedHeight(ra->sizeHint().height());

    // Dodanie obszaru technicznego __________________________________________

    QLabel *howto = new QLabel("Klikaj w zakratkowanym polu myszka, aby utworzyc<br>"
                               "wielokat. Uzywaj ponizszych przyciskow, by<br>"
                               "wyczyscic pole rysunkowe lub przemiescic wielokat<br>"
                               "o podane wspolrzedne.");

    QPushButton *clearPoly = new QPushButton("&Czysc pole rysunkowe");
    QObject::connect(clearPoly,SIGNAL(clicked()),ra,SLOT(clearPoly()));

    QLineEdit *edReposX = new QLineEdit;
    edReposX->setText(QString("0"));
    QIntValidator *valX = new QIntValidator(-ra->width(),ra->width(),edReposX);
    edReposX->setValidator(valX);
    QObject::connect(edReposX,SIGNAL(textChanged(QString)),ra,SLOT(setNewX(QString)));

    QLabel *labReposX = new QLabel("&X:");
    labReposX->setBuddy(edReposX);

    QLineEdit *edReposY = new QLineEdit;
    edReposY->setText(QString("0"));
    QIntValidator *valY = new QIntValidator(-ra->height(),ra->height(),edReposY);
    edReposY->setValidator(valY);
    QObject::connect(edReposY,SIGNAL(textChanged(QString)),ra,SLOT(setNewY(QString)));

    QLabel *labReposY = new QLabel("&Y:");
    labReposY->setBuddy(edReposY);

    QPushButton *reposOk = new QPushButton("&Przesun o wektor");
    QObject::connect(reposOk,SIGNAL(clicked()),ra,SLOT(movePoly()));

    QPushButton *reposReset = new QPushButton("&Reset pozycji");
    QObject::connect(reposReset,SIGNAL(clicked()),ra,SLOT(unMovePoly()));

    // Zabawa layoutami ______________________________________________________

    QVBoxLayout *right = new QVBoxLayout;
    QGridLayout *repos = new QGridLayout;

    repos->addWidget(clearPoly,1,3,Qt::AlignRight);
    repos->setRowMinimumHeight(2,60);
    repos->addWidget(labReposX,3,1);
    repos->addWidget(labReposY,4,1);
    repos->addWidget(edReposX,3,2,1,2,Qt::AlignLeft);
    repos->addWidget(edReposY,4,2,1,2,Qt::AlignLeft);
    repos->addWidget(reposOk,5,1,Qt::AlignLeft);
    repos->addWidget(reposReset,5,2,Qt::AlignLeft);

    right->addWidget(howto);
    right->addLayout(repos);
    right->addStretch();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(ra);
    layout->addLayout(right);

    // Prace wykończeniowe ___________________________________________________

    window->setLayout(layout);
    window->setFixedHeight(window->sizeHint().height());
    window->setFixedWidth(window->sizeHint().width());
    window->show();

    // W sumie koniec ________________________________________________________

    return app.exec();
}
