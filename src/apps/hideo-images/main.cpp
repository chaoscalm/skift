#include <hideo-base/scafold.h>
#include <karm-image/loader.h>
#include <karm-sys/entry.h>
#include <karm-ui/app.h>
#include <karm-ui/dialog.h>

#include "app.h"

namespace Hideo::Images {

Ui::Child app(State initial) {
    return Ui::reducer<Model>(
        initial,
        [](auto const &state) {
            return scafold({
                .icon = Mdi::IMAGE,
                .title = "Images"s,
                .body = slot$(
                    state.isEditor
                        ? editor(state)
                        : viewer(state)
                ),
            });
        }
    );
}

} // namespace Hideo::Images

Async::Task<> entryPointAsync(Sys::Context &ctx) {
    auto &args = useArgs(ctx);
    Res<Image::Picture> image = Error::invalidInput("No image provided");

    if (args.len()) {
        auto url = co_try$(Mime::parseUrlOrPath(args[0]));
        image = Image::load(url);
    }

    co_return Ui::runApp(ctx, Hideo::Images::app(image));
}
