#ifndef CWS_SCENEMANAGER_H
#define CWS_SCENEMANAGER_H

namespace cws {

	class IScene;

	struct SceneNode {
		IScene* scene_ptr;
		SceneNode* next;
	};

	class SceneManager {
		public:
			SceneManager();

			void push(IScene* scene_ptr);
			IScene* pop();
			IScene* peek() const;
			bool is_empty() const;
			void clear();
		private:
			SceneNode* m_top;
	};

};

#endif