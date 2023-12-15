#ifndef CWS_WINDOWCONFIG_H
#define CWS_WINDOWCONFIG_H

namespace cws::settings {

	struct WindowSettings {
		int width, height;
		const char* title;

		WindowSettings() : 
			width(600), 
			height(400), 
			title("CWS App") 
		{}
		
		WindowSettings(int w, int h, const char* t) :
			width(w),
			height(h),
			title(t)
		{}
	};

};

#endif