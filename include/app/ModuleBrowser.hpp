#pragma once
#include <app/common.hpp>
#include <widget/Widget.hpp>


namespace rack {
namespace app {

enum SortMethod {
	Alphabetic_ASC,
	Alphabetic_DESC,
	LastModified_ASC,
	LastModified_DESC,
	Size_ASC,
	Size_DESC,
	Uses_ASC,
	Uses_DESC,
};

widget::Widget* moduleBrowserCreate();


} // namespace app
} // namespace rack
