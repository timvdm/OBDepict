#include <cairopainter.h>

#include <iostream>
using namespace std;

namespace OpenBabel
{

  CairoPainter::CairoPainter() : m_surface(0), m_cairo(0), m_fontPointSize(12)
  {
  }

  CairoPainter::~CairoPainter()
  {
    if (m_cairo)
      cairo_destroy(m_cairo);
    if (m_surface)
      cairo_surface_destroy(m_surface);
  }

  void CairoPainter::NewCanvas(double width, double height)
  {
    // clean up
    if (m_cairo)
      cairo_destroy(m_cairo);
    if (m_surface)
      cairo_surface_destroy(m_surface);
    // create new surface to paint on
    m_surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    m_cairo = cairo_create(m_surface);
  }
  
  bool CairoPainter::IsGood() const
  {
    if (!m_cairo)
      return false;
    if (!m_surface)
      return false;
    return true;
  }
      
  void CairoPainter::SetFontSize(int pointSize)
  {
    m_fontPointSize = pointSize;
    cairo_set_font_size(m_cairo, pointSize);
  }

  void CairoPainter::SetFillColor(const OBColor &color)
  {
    cairo_set_source_rgb(m_cairo, color.red, color.green, color.blue);
  }

  void CairoPainter::SetPenColor(const OBColor &color)
  {
    cairo_set_source_rgb(m_cairo, color.red, color.green, color.blue);
  }
      
  void CairoPainter::SetPenWidth(double width)
  {
    cairo_set_line_width(m_cairo, width);
  }

  void CairoPainter::DrawLine(double x1, double y1, double x2, double y2)
  {
    cairo_move_to(m_cairo, x1, y1);
    cairo_line_to(m_cairo, x2, y2);
    cairo_stroke(m_cairo);
  }

  void CairoPainter::DrawPolygon(const std::vector<std::pair<double,double> > &points)
  {
    std::vector<std::pair<double,double> >::const_iterator i;
    for (i = points.begin(); i != points.end(); ++i)
      cairo_line_to(m_cairo, i->first, i->second); // note: when called without previous point, 
                                                   //       this function behaves like cairo_move_to 
    cairo_stroke(m_cairo);
  }

  void CairoPainter::DrawCircle(double x, double y, double r)
  {
    cairo_arc(m_cairo, x, y, r, 0, 2 * M_PI);
    cairo_stroke(m_cairo);
  }

  void CairoPainter::DrawText(double x, double y, const std::string &text)
  {
    cairo_move_to(m_cairo, x, y);
    cairo_show_text(m_cairo, text.c_str());

    //m_canvas.draw( Magick::DrawableText(x, y, text) );
    // draw square around text for debugging
    /*
       OBFontMetrics metrics = GetFontMetrics(text);
       m_canvas.draw( Magick::DrawableLine(x, y, x + metrics.width, y) ); // bottom
       m_canvas.draw( Magick::DrawableLine(x, y - metrics.ascent, x + metrics.width, y - metrics.ascent) ); // top
       m_canvas.draw( Magick::DrawableLine(x, y, x, y - metrics.ascent) ); // left
       m_canvas.draw( Magick::DrawableLine(x + metrics.width, y, x + metrics.width, y - metrics.ascent) ); // right
       */
  }

  OBFontMetrics CairoPainter::GetFontMetrics(const std::string &text)
  {
    cairo_font_extents_t fe;
    cairo_font_extents(m_cairo, &fe);
    cairo_text_extents_t te;
    cairo_text_extents(m_cairo, text.c_str(), &te);

    OBFontMetrics metrics;
    metrics.fontSize = m_fontPointSize;
    metrics.ascent = fe.ascent;
    metrics.descent = -fe.descent;
    metrics.width = te.width;
    metrics.height = fe.height;
    return metrics;
  }
      
  void CairoPainter::WriteImage(const std::string &filename)
  {
    if (!m_cairo || !m_surface)
      return;
    
    cairo_surface_write_to_png(m_surface, filename.c_str());
  }

}

