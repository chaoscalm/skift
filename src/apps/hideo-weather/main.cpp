#include <karm-main/main.h>
#include <karm-ui/app.h>
#include <karm-ui/scafold.h>
#include <karm-ui/scroll.h>

namespace Hideo::Weather {

Ui::Child app() {
    return Ui::scafold({
        .icon = Mdi::WEATHER_PARTLY_CLOUDY,
        .title = "Weather",
        .body = Ui::image(Media::loadImage("bundle://hideo-weather/images/weather-few-clouds.jpg"_url).unwrap()) | Ui::cover(),
        .size = {460, 320},
    });
}

} // namespace Hideo::Weather

Res<> entryPoint(Ctx &ctx) {
    return Ui::runApp(ctx, Hideo::Weather::app());
}
