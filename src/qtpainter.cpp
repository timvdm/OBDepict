#include <qtpainter.h>

#include <QGraphicsTextItem>
#include <QFontMetrics>

#include <iostream>
using std::cout;
using std::endl;

namespace OpenBabel
{

  QtPainter::QtPainter()
  {
  }

  void QtPainter::NewCanvas(double width, double height)
  {
    m_scene->clear();
    m_scene->setSceneRect(0.0, 0.0, width, height);
  }

  bool QtPainter::IsGood() const
  {
    if (m_scene)
      return true;
    return false;
  }
      
  void QtPainter::SetFontFamily(const std::string &fontFamily)
  {
    m_font.setFamily(fontFamily.c_str());
  }
      
  void QtPainter::SetFontSize(int pointSize)
  {
    m_font.setPointSize(pointSize);
  }

  void QtPainter::SetFillColor(const OBColor &color)
  {
    m_brush = QBrush(ToQColor(color));
  }

  void QtPainter::SetPenColor(const OBColor &color)
  {
    m_pen.setColor(ToQColor(color));
  }
      
  void QtPainter::SetPenWidth(double width)
  {
    m_pen.setWidthF(width);
  }

  void QtPainter::DrawLine(double x1, double y1, double x2, double y2)
  {
    m_scene->addLine( QLineF(x1, y1, x2, y2), m_pen );
  }

  void QtPainter::DrawPolygon(const std::vector<std::pair<double,double> > &points)
  {
    QVector<QPointF> coords;
    std::vector<std::pair<double,double> >::const_iterator i;
    for (i = points.begin(); i != points.end(); ++i)
      coords.push_back( QPointF(i->first, i->second) );
    m_scene->addPolygon( QPolygonF(coords), m_pen, m_brush );
  }

  void QtPainter::DrawCircle(double x, double y, double r)
  {
    double d = r+r;
    m_scene->addEllipse(x-r, y-r, d, d, m_pen, m_brush);
  }

  void QtPainter::DrawText(double x, double y, const std::string &text)
  {
    QGraphicsTextItem *item = m_scene->addText(text.c_str(), m_font);
    OBFontMetrics fm = GetFontMetrics(text);
    item->setPos(x, y - fm.ascent);
  }

  OBFontMetrics QtPainter::GetFontMetrics(const std::string &text)
  {
    QFontMetrics type(m_font);

    cout << "type.textWidth() = " << type.width(text.c_str()) << endl;

    OBFontMetrics metrics;
    metrics.fontSize = m_font.pointSize();
    metrics.ascent = type.ascent();
    metrics.descent = -type.descent();
    metrics.width = type.width(text.c_str());
    metrics.height = type.height();
    return metrics;
  }
      
  void QtPainter::SetScene(QGraphicsScene *scene)
  {
    m_scene = scene;
  }

  QColor QtPainter::ToQColor(const OBColor &color)
  {
    return QColor(255*color.red, 255*color.green, 255*color.blue);
  }

}

