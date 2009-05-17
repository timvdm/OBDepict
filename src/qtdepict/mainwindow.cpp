#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <openbabel/obconversion.h>
#include <openbabel/mol.h>

#include <OBDepict>
#include <qtpainter.h>

#include <QDebug>

using namespace OpenBabel;

class MainWindowPrivate
{
  public:
    MainWindowPrivate() : mol(new OBMol), painter(new QtPainter), depictor(new OBDepict(painter))
    {
    }
    ~MainWindowPrivate()
    {
      delete depictor;
      delete painter;
      delete mol;
    }

    OBMol *mol;
    QtPainter *painter;
    OBDepict *depictor;
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    d(new MainWindowPrivate)
{
  m_ui->setupUi(this);

  QGraphicsScene *scene = new QGraphicsScene(m_ui->graphicsView);
  m_ui->graphicsView->setScene(scene);

  connect(m_ui->fontFamilyComboBox, SIGNAL(currentFontChanged(const QFont&)), this, SLOT(fontFamilyChanged(const QFont&)));
  connect(m_ui->fontSizeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(fontSizeChanged(int)));
  connect(m_ui->bondLengthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bondLengthChanged(double)));
  connect(m_ui->penWidthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(penWidthChanged(double)));
  connect(m_ui->bondWidthSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bondWidthChanged(double)));
  connect(m_ui->bondSpacingSpinBox, SIGNAL(valueChanged(double)), this, SLOT(bondSpacingChanged(double)));


}

MainWindow::~MainWindow()
{
    delete m_ui;
    delete d;
}

void MainWindow::fontFamilyChanged(const QFont &font)
{
  d->depictor->SetFontFamily(font.family().toStdString());
  d->depictor->DrawMolecule(d->mol);
}

void MainWindow::fontSizeChanged(int index)
{
  // font sizes in the QComboBox range from 2 to 36 in steps of 2
  d->depictor->SetFontSize(2*index);
  d->depictor->DrawMolecule(d->mol);
}

void MainWindow::bondLengthChanged(double value)
{
  d->depictor->SetBondLength(value);
  d->depictor->DrawMolecule(d->mol);
}

void MainWindow::penWidthChanged(double value)
{
  d->depictor->SetPenWidth(value);
  d->depictor->DrawMolecule(d->mol);
}

void MainWindow::bondWidthChanged(double value)
{
  d->depictor->SetBondWidth(value);
  d->depictor->DrawMolecule(d->mol);
}

void MainWindow::bondSpacingChanged(double value)
{
  d->depictor->SetBondSpacing(value);
  d->depictor->DrawMolecule(d->mol);
}



void MainWindow::loadFile(const QString &filename)
{
  qDebug() << "MainWindow::loadFile(" << filename << ")";
  // read a molecule
  OBConversion conv;
  OBFormat *format = conv.FormatFromExt(filename.toStdString().c_str());
  conv.SetInFormat(format);

  std::ifstream ifs;
  ifs.open(filename.toStdString().c_str());
  if (!ifs) {
    qDebug() << "Could not open " << filename;
    return;
  }

  if (!conv.Read(d->mol, &ifs)) {
    qDebug() << "Could not read molecule from " << filename;
    return;
  }
 
  d->painter->SetScene(m_ui->graphicsView->scene());
 
  // depict the molecule
  d->depictor->DrawMolecule(d->mol);
  //depictor.AddAtomLabels(&mol, OBDepict::AtomId);
    
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

