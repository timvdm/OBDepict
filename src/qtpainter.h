#ifndef OB_QTPAINTER_H
#define OB_QTPAINTER_H

#include <OBDepict>
#include <QGraphicsScene>

namespace OpenBabel
{
  class QtPainter : public OBPainter
  {
    public:
      QtPainter();
      //! @name OBPainter methods
      //@{
      void NewCanvas(double width, double height);
      bool IsGood() const;
      void SetFontSize(int pointSize);
      void SetFontFamily(const std::string &fontFamily);
      void SetFillColor(const OBColor &color);
      void SetPenColor(const OBColor &color);
      void SetPenWidth(double width);
      void DrawLine(double x1, double y1, double x2, double y2);
      void DrawPolygon(const std::vector<std::pair<double,double> > &points);
      void DrawCircle(double x, double y, double r);
      void DrawText(double x, double y, const std::string &text);
      OBFontMetrics GetFontMetrics(const std::string &text);
      //@}

      //! @name QtPainter specific
      //@{
      void SetScene(QGraphicsScene *scene);
      QColor ToQColor(const OBColor &color);
      //@}
    private:
      QFont           m_font;
      QPen            m_pen;
      QBrush          m_brush;
      QGraphicsScene *m_scene;
  };
}

#endif
