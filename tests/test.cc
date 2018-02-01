#include "graphics/imageloader.h"
#include "graphics/filters/gaussian_blur.h"
#include "graphics/canvas.h"
#include "graphics/genericgraphic.h"

int l_ref = 70;

bool isMoon(const Sine::RGBA &r) {
    return (Sine::ColorUtils::getLuminance(r) > l_ref);
}

std::string pad(int f_n) {
    std::string ret;
    std::string l_k = std::to_string(f_n);
    for (int i = 0; i < 3 - l_k.length(); i++) {
        ret += '0';
    }
    ret += l_k;

    return ret;
}

int main() {
    Sine::Canvas output_image{1440, 1440};
    for (int f_n = 685; f_n < 686; f_n++) {
        Sine::Canvas image_temp{"/Users/timoothy/Desktop/eclipse2018/2018_01_31/IMG_0" + pad(f_n) + ".JPG"};

        int width = image_temp.getWidth();
        int height = image_temp.getHeight();

        Sine::Bitmap image{width, height};

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                image.setPixel(i, j, isMoon(image_temp.getPixel(i, j, false)), false);
            }
        }


        const int threshold = 9;
        const int precount_thresh = 27;
        const int count_thresh = 8;

        int best_x = 0;
        int best_y = 0;
        int bestR = 1000;

        long avg_x = 0;
        long avg_y = 0;
        int cnt = 0;

        for (int i = 0; i < image_temp.getWidth(); i++) {
            for (int j = 0; j < image_temp.getHeight(); j++) {
                if (image.getPixel(i, j, false)) {
                    avg_x += i;
                    avg_y += j;
                    cnt++;
                }
            }
        }

        const int radius = 400;

        const int rad_min = 310;
        const int rad_max = 370;

        int best_xs = avg_x / cnt;
        int best_ys = avg_y / cnt;

        std::cout << best_xs << ' ' << best_ys << '\n';

        for (int i = std::max(0, best_xs - radius); i < std::min(image_temp.getWidth(), best_xs + radius); i += 10) {
            for (int j = std::max(0, best_ys - radius);
                 j < std::min(image_temp.getHeight(), best_ys + radius); j += 10) {
                int r;
                bool precount_f = false;

                for (r = rad_min; r < rad_max; r += 6) {
                    int count = 0;
                    for (double c = 0; c < 2 * 3.1415926535; c += 0.05) {
                        int x = i + r * std::cos(c);
                        int y = j + r * std::sin(c);

                        count += image.pairContained(x, y) && image.getPixel(x, y, false);

                        if (count > precount_thresh) {
                            precount_f = true;
                        }
                    }

                    if (precount_f && count < count_thresh) {
                        break;
                    }
                }

                if (r == rad_min || r == rad_max) continue;

                if (r < bestR) {
                    bestR = r;
                    best_x = i;
                    best_y = j;
                }
            }
        }

        int i = best_x;
        int j = best_y;
        int r = bestR;

        /*std::cout << bestR << std::endl;
        std::cout << best_x << std::endl;
        std::cout << best_y << std::endl;*/

        output_image.fill(Sine::RGBA(0, 0, 0, 255));
        output_image.mixImage(image_temp, -best_x + 1440 / 2, -best_y + 1440 / 2, Sine::ColorUtils::ColorMix::ADDITION);

        output_image.exportToJPEG("/Users/timoothy/Desktop/l_k/test" + std::to_string(f_n) + ".jpg");
    }
}
