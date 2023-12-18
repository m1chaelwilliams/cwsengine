#ifndef CWS_SCENE_H
#define CWS_SCENE_H

namespace cws {

	class IScene {
		public:
			virtual void on_load() = 0;
			virtual void on_unload() = 0;
			virtual void on_update() = 0;
			virtual void on_draw() = 0;
	};

}

#endif