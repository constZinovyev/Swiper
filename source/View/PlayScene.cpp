#include "PlayScene.h"

void PlayScene::UpdateView(){
    

}
void PlayScene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
    field.updateField(modelForView.getStack());
    playerBlc.updateBlocks(modelForView.getPlayerRow());
    Scene::Update(deltaTime, alphaMul);
}

void PlayScene::Render()
{
    Scene::Render();
}

PlayScene::PlayScene(GameModel &gameMdl):modelForView(gameMdl){
    Scene::Init();
    background = new CSprite();
    background->SetImage(g_pResources->getMenuBG());
    background->m_X = 0;
    background->m_Y = 0;
    if (Iw2DGetSurfaceHeight() == 568)
    {
        background->m_ScaleX = 0.5f;
        background->m_ScaleY = 0.5f;
    }
    AddChild(background);
    playerBlc.addToScene(this);
    field.addToScene(this);
}

PlayScene::~PlayScene(){
    
    
}