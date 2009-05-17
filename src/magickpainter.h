#ifndef OB_MAGICKPAINTER_H
#define OB_MAGICKPAINTER_H

#include <OBDepict>
#include <Magick++.h>

namespace OpenBabel
{
  class MagickPainter : public OBPainter
  {
    public:
      //! @name OBPainter methods
      //@{
      void NewCanvas(double width, double height);
      bool IsGood() const;
      void SetFontFamily(const std::string &fontFamily) {} // FIXME
      void SetFontSize(int pointSize);
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
      void WriteImage(const std::string &filename);
      //@}
 
    private:
      Magick::Image m_canvas;
  };
}

#endif
