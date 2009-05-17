#include <magickpainter.h>

#include <iostream>
using namespace std;

namespace OpenBabel
{
  
  void MagickPainter::NewCanvas(double width, double height)
  {
    m_canvas = Magick::Image( Magick::Geometry(width, height), "white" );
  }
  
  bool MagickPainter::IsGood() const
  {
    return m_canvas.geometry().isValid();
  }
      
  void MagickPainter::SetFontSize(int pointSize)
  {
    m_canvas.fontPointsize(pointSize);
  }

  void MagickPainter::SetFillColor(const OBColor &color)
  {
    m_canvas.fillColor( Magick::ColorRGB(color.red, color.green, color.blue) );
  }

  void MagickPainter::SetPenColor(const OBColor &color)
  {
    m_canvas.strokeColor( Magick::ColorRGB(color.red, color.green, color.blue) );
  }
      
  void MagickPainter::SetPenWidth(double width)
  {
    m_canvas.strokeWidth(width);
  }

  void MagickPainter::DrawLine(double x1, double y1, double x2, double y2)
  {
    m_canvas.draw( Magick::DrawableLine(x1, y1, x2, y2) );      
  }

  void MagickPainter::DrawPolygon(const std::vector<std::pair<double,double> > &points)
  {
    std::list<Magick::Coordinate> coords;
    std::vector<std::pair<double,double> >::const_iterator i;
    for (i = points.begin(); i != points.end(); ++i)
      coords.push_back( Magick::Coordinate(i->first, i->second) );
    m_canvas.draw( Magick::DrawablePolygon(coords) );      
  }

  void MagickPainter::DrawCircle(double x, double y, double r)
  {
    m_canvas.draw( Magick::DrawableCircle(x, y, x - r, y) );
  }

  void MagickPainter::DrawText(double x, double y, const std::string &text)
  {
    // m_canvas.boxColor(Magick::Color("yellow")); <- results unsatisfactory...
    m_canvas.draw( Magick::DrawableText(x, y, text) );
    // draw square around text for debugging
    /*
       OBFontMetrics metrics = GetFontMetrics(text);
       m_canvas.draw( Magick::DrawableLine(x, y, x + metrics.width, y) ); // bottom
       m_canvas.draw( Magick::DrawableLine(x, y - metrics.ascent, x + metrics.width, y - metrics.ascent) ); // top
       m_canvas.draw( Magick::DrawableLine(x, y, x, y - metrics.ascent) ); // left
       m_canvas.draw( Magick::DrawableLine(x + metrics.width, y, x + metrics.width, y - metrics.ascent) ); // right
       */
  }

  OBFontMetrics MagickPainter::GetFontMetrics(const std::string &text)
  {
    Magick::TypeMetric type;
    m_canvas.fontTypeMetrics(text, &type);

    cout << "type.textWidth() = " << type.textWidth() << endl;

    OBFontMetrics metrics;
    metrics.fontSize = m_canvas.fontPointsize();
    metrics.ascent = type.ascent();
    metrics.descent = type.descent();
    metrics.width = type.textWidth();
    metrics.height = type.textHeight();
    return metrics;
  }
      
  void MagickPainter::WriteImage(const std::string &filename)
  {
    m_canvas.write(filename);
  }

}

