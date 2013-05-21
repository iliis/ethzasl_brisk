/*

 Copyright (c) 2013, Simon Lynen, ASL, ETH Zurich, Switzerland
 You can contact the author at <slynen at ethz dot ch>

 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.
 * Neither the name of ETHZ-ASL nor the
 names of its contributors may be used to endorse or promote products
 derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL ETHZ-ASL BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef FALSECOLOR_H_
#define FALSECOLOR_H_

#include <opencv2/core/core.hpp>
#include <opencv2/contrib/retina.hpp>
#include <boost/shared_ptr.hpp>

class converter_16_8
{
  enum
  {
    histminmembersperbucket = 10,
  };
private:
  double max_;
  double min_;
  static converter_16_8* inst_;
  bool firstframe_;
  boost::shared_ptr<cv::Retina> retina_;
public:
  converter_16_8();
  ~converter_16_8();
  static converter_16_8& Instance()
  {
    if (!inst_)
    {
      inst_ = new converter_16_8;
    }
    return *inst_;
  }
  double getMax();
  double getMin();
  void convert_to8bit(const cv::Mat& img16, cv::Mat& img8, bool doTempConversion);
  void toneMapping(const cv::Mat& img16, cv::Mat& img8);
};

struct color
{
  unsigned char rgbBlue;
  unsigned char rgbGreen;
  unsigned char rgbRed;
  color()
  {
    rgbBlue = rgbGreen = rgbRed = 0;
  }
};

struct palette
{
  enum palettetypes{
    Linear_red_palettes, GammaLog_red_palettes, Inversion_red_palette, Linear_palettes, GammaLog_palettes,
    Inversion_palette, False_color_palette1, False_color_palette2, False_color_palette3, False_color_palette4
  };
  color colors[256];
};

palette GetPalette(palette::palettetypes pal);

void convertFalseColor(const cv::Mat& srcmat, cv::Mat& dstmat, palette::palettetypes paltype, bool drawlegend = false, double mintemp = 0, double maxtemp = 0);

#endif /* FALSECOLOR_H_ */