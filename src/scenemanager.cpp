#include "world/scenemanager.h"
#include "world/scene.h"
#include "utils/debug.h"

using namespace cws;

SceneManager::SceneManager() :
	m_top(nullptr)
{}

IScene* SceneManager::pop() {
	if (is_empty()) {
		return nullptr;
	}

	SceneNode* target = m_top;
	m_top = m_top->next;

	return target->scene_ptr;
}

void SceneManager::push(IScene* scene_ptr) {
	SceneNode* new_node = new SceneNode;
	new_node->scene_ptr = scene_ptr;
	new_node->next = m_top;

	m_top = new_node;
}

IScene* SceneManager::peek() const {
	if (!m_top) {
		return nullptr;
	}
	return m_top->scene_ptr;
}

void SceneManager::clear() {

	CWS_LOGLN("--- Deallocating scene manager... ---");

	while (m_top) {
		CWS_LOGLN("- Deallocating scene");

		SceneNode* target = m_top;

		m_top = m_top->next;

		delete target->scene_ptr;
		delete target;
	}
	
	m_top = nullptr;
}

bool SceneManager::is_empty() const {
	return m_top == nullptr;
}