#include "Story.h"

std::string Story::getName()
{
    return this->_name;
}

std::string Story::getInfo()
{
    return this->_info;
}

std::string Story::getAuthor()
{
    return this->_author;
}

std::string Story::getDate()
{
    return this->_date;
}

int Story::loadStory(std::fstream* file)
{
    if (!this->_isHeaderOkay(file)) {
        std::cout << "header error" << std::endl;
        return 1;
    }

    if (!this->_isSizeOkay(file)) {
        std::cout << "size error" << std::endl;
        return 2;
    }

    this->_loadGlobalInfo(file);
    std::cout << "name: " << this->_name << std::endl;
    std::cout << "info: " << this->_info << std::endl;
    std::cout << "author: " << this->_author << std::endl;
    std::cout << "date: " << this->_date << std::endl;
    std::cout << std::endl;

    this->_loadCharacters(file);
    this->_loadCCE(file);
    this->_loadEvents(file);
    this->_loadImages(file);
    this->_loadMPE(file);
    this->_loadMessages(file);
    this->_loadMusics(file);
    this->_loadSfxs(file);
    this->_loadCompilationInfo(file);
    if (!this->_checkEndOfFile(file)) {
        std::cout << "end of file error" << std::endl;
        return 1;
    }
    this->_Player = new Protagonist();
    system("pause");

    return 0;
}

int Story::play()
{
    Message* currentMessage = this->_findMessageById(1);
    if (currentMessage) {
        ChooseClothesEvent* currentCCE = NULL;
        MakeProtagonistEvent* currentMPE = NULL;
        Event* currentEvent = NULL;

        while (1)
        {
            if (currentMessage) {
                this->_clsAndShowInfo();
                this->_showMessage(currentMessage);
                int nextMessage = currentMessage->getNextMessage();

                if (nextMessage != 0) {
                    currentMessage = this->_findMessageById(nextMessage);
                }
                else {
                    int nextEvent = currentMessage->getNextEvent();
                    currentMessage = NULL;

                    currentEvent = this->_findEventById(nextEvent);
                }
            }
            else if (currentEvent) {
                this->_clsAndShowInfo();
                if (!currentEvent->getPlayerOptions().empty()) {
                    this->_showEvent(currentEvent);

                    int nextMessage;
                    std::cin >> nextMessage;

                    std::vector<int> nextMessages = currentEvent->getNextMessages();
                    currentEvent = NULL;
                    currentMessage = this->_findMessageById(nextMessages[nextMessage]);
                }
                else {
                    int mpei = currentEvent->getMpei();
                    int ccei = currentEvent->getCcei();
                    if (mpei != 0) {
                        currentEvent = NULL;
                        currentMPE = this->_getMpei();
                    }
                    else if (ccei != 0) {
                        currentEvent = NULL;
                        currentCCE = this->_findCceById(ccei);
                    }
                    else {
                        std::cout << "cant find whats next" << std::endl;
                    }
                }
            }
            else if (currentMPE) {
                this->_clsAndShowInfo();
                this->_showMPE(currentMPE);

                int nextMessageId = currentMPE->getNextMessageId();
                currentMessage = this->_findMessageById(nextMessageId);
                currentMPE = NULL;
            }
            else if (currentCCE) {
                this->_clsAndShowInfo();
                this->_showCCE(currentCCE);

                int nextMessageId = currentCCE->getNextMessageId();
                currentCCE = NULL;
                currentMessage = this->_findMessageById(nextMessageId);
            }
            else {
                return 0;
            }
        }
    }
    else {
        return 1; //cant find starting message
    }

    return 0;
}

Event* Story::_findEventById(int id)
{
    for (int i = 0; i < this->_Events.size(); i++) {
        if (this->_Events[i].getId() == id) {
            return &this->_Events[i];
        }
    }
    return nullptr;
}

Message* Story::_findMessageById(int id)
{
    for (int i = 0; i < this->_Messages.size(); i++) {
        if (this->_Messages[i].getId() == id) {
            return &this->_Messages[i];
        }
    }
    return nullptr;
}


MakeProtagonistEvent* Story::_getMpei()
{
    return this->_MPEvent;
}

ChooseClothesEvent* Story::_findCceById(int id)
{
    for (int i = 0; i < this->_CCEvents.size(); i++) {
        if (this->_CCEvents[i].getId() == id) {
            return &this->_CCEvents[i];
        }
    }
    return nullptr;
}

Image* Story::_findImageById(int id)
{
    for (int i = 0; i < this->_Images.size(); i++) {
        if (this->_Images[i].getId() == id) {
            return &this->_Images[i];
        }
    }
    return nullptr;
}

Music* Story::_findMusicById(int id)
{
    for (int i = 0; i < this->_Musics.size(); i++) {
        if (this->_Musics[i].getId() == id) {
            return &this->_Musics[i];
        }
    }
    return nullptr;
}

Sfx* Story::_findSfxById(int id)
{
    for (int i = 0; i < this->_Sfxs.size(); i++) {
        if (this->_Sfxs[i].getId() == id) {
            return &this->_Sfxs[i];
        }
    }
    return nullptr;
}

Protagonist* Story::_getPlayer()
{
    return this->_Player;
}

void Story::_clsAndShowInfo()
{
    system("cls");
    std::cout << "name: " << this->_name << std::endl;
    std::cout << "info: " << this->_info << std::endl;
    std::cout << "author: " << this->_author << std::endl;
    std::cout << "date: " << this->_date << std::endl;
    std::cout << std::endl;
    std::cout << "compilation info: " << std::endl;
    std::cout << this->_compilationInfo << "\n\n";
}

void Story::_showMessage(Message* m)
{
    std::cout << "id: " << m->getId() << std::endl;
    std::cout << "character id: " << m->getCharacterId() << std::endl;
    std::cout << "musics id: ";
    for (int i = 0; i < m->getAllMusicId().size(); i++) {
        std::cout << m->getAllMusicId()[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "sfxs id: ";
    for (int i = 0; i < m->getAllSfxId().size(); i++) {
        std::cout << m->getAllSfxId()[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "sprite id: " << m->getSpriteId() << std::endl;
    std::cout << "animation id: " << m->getAnimationId() << std::endl;
    std::cout << "clothes id: " << m->getClothesId() << std::endl;
    std::cout << "bg image id: " << m->getBgImageId() << std::endl;
    std::cout << "next message id: " << m->getNextMessage() << std::endl;
    std::cout << "next event id: " << m->getNextEvent() << std::endl;
    std::cout << "message x: " << m->getMessageX() << std::endl;
    std::cout << "message y: " << m->getMessageY() << std::endl;
    std::cout << "character x: " << m->getCharacterX() << std::endl;
    std::cout << "character y: " << m->getCharacterY() << std::endl;
    std::cout << std::endl;

    std::cout << "message: " << std::endl;
    std::cout << m->getText() << std::endl;
    system("pause");
}

void Story::_showEvent(Event* e)
{
    std::cout << "id: " << e->getId() << std::endl;
    std::cout << "next messages: ";
    for (int i = 0; i < e->getNextMessages().size(); i++) {
        std::cout << e->getNextMessages()[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "next events: ";
    for (int i = 0; i < e->getNextEvents().size(); i++) {
        std::cout << e->getNextEvents()[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "mpeid: " << e->getMpei() << std::endl;
    std::cout << "cceid: " << e->getCcei() << std::endl;
    std::cout << "show: " << e->isShowed() << std::endl;
    std::cout << std::endl;
    std::cout << "Take your time and choose: " << std::endl;
    for (int i = 0; i < e->getPlayerOptions().size(); i++) {
        std::cout << "[" << i << "] " << e->getPlayerOptions()[i] << std::endl;
    }
    std::cout << std::endl;
}

void Story::_showMPE(MakeProtagonistEvent* mpe)
{
    std::cout << "next message id: " << mpe->getNextMessageId() << std::endl;
    std::cout << std::endl;

    std::cout << mpe->getText() << std::endl;
    std::cout << "DefaultName = " << mpe->getName() << std::endl;
    std::cout << "Enter your name: ";
    std::string name;
    std::cin >> name;
    this->_getPlayer()->setName(name);

    int playerInput = 0;

    std::cout << "Select your skin color: " << std::endl;
    for (int i = 0; i < mpe->getSkins().size(); i++) {
        std::cout << "[" << i << "] " << mpe->getSkins()[i][0] << std::endl;
    }
    std::cin >> playerInput;
    this->_getPlayer()->setGSkins(mpe->getSkins()[playerInput]);

    std::cout << "Select your face: " << std::endl;
    for (int i = 0; i < mpe->getFaces().size(); i++) {
        std::cout << "[" << i << "] " << mpe->getFaces()[i][0] << std::endl;
    }
    std::cin >> playerInput;
    this->_getPlayer()->setGFaces(mpe->getFaces()[playerInput]);

    std::cout << "Select your hair color: " << std::endl;
    for (int i = 0; i < mpe->getHairs().size(); i++) {
        std::cout << "[" << i << "] " << mpe->getHairs()[i][0] << std::endl;
    }
    std::cin >> playerInput;
    this->_getPlayer()->setGHairs(mpe->getHairs()[playerInput]);

    this->_printInfoAboutPlayer();
    system("pause");
}

void Story::_showCCE(ChooseClothesEvent* cce)
{
    std::cout << "id: " << cce->getId() << std::endl;
    std::cout << "next message id: " << cce->getNextMessageId() << std::endl;
    std::cout << std::endl;

    std::cout << cce->getText() << std::endl;
    for (int i = 0; i < cce->getClothes().size(); i++) {
        std::cout << "[" << i << "] " << cce->getClothes()[i][0] << std::endl;
    }
    int playerInput = 0;
    std::cin >> playerInput;
    this->_getPlayer()->setGClothes(cce->getClothes()[playerInput]);

    std::cout << "Player clothes: " << std::endl;
    for (int i = 0; i < this->_getPlayer()->getGClothes().size(); i++) {
        std::cout << this->_getPlayer()->getGClothes()[i] << std::endl;
    }
    std::cout << std::endl;
    system("pause");
}

void Story::_printInfoAboutPlayer()
{
    int id = this->_getPlayer()->getCurrentSpriteId();
    Image* skin = this->_findImageById(this->_getPlayer()->getGSkins()[id]);
    Image* face = this->_findImageById(this->_getPlayer()->getGFaces()[id]);
    Image* hairs = this->_findImageById(this->_getPlayer()->getGHairs()[id]);

    std::cout << std::endl;
    std::cout << "Name: " << this->_name << std::endl;

    if (skin != nullptr) {
        std::cout << "Current skin: " << skin->getName() << std::endl;
    }
    else {
        std::cout << "Current skin: not found image with id: " << this->_getPlayer()->getGSkins()[id] << std::endl;
    }

    if (face != nullptr) {
        std::cout << "Current face: " << face->getName() << std::endl;
    }
    else {
        std::cout << "Current face: not found image with id: " << this->_getPlayer()->getGFaces()[id] << std::endl;
    }

    if (hairs != nullptr) {
        std::cout << "Current hairs: " << hairs->getName() << std::endl;
    }
    else {
        std::cout << "Current hairs: not found image with id: " << this->_getPlayer()->getGHairs()[id] << std::endl;
    }
    
    if (!this->_getPlayer()->getGClothes().empty()) {
        Image* clothes = this->_findImageById(this->_getPlayer()->getGClothes()[id]);
        if (clothes != nullptr) {
            std::cout << "Current clothes: " << clothes->getName() << std::endl;
        }
        else {
            std::cout << "Current clothes: not found image with id: " << this->_getPlayer()->getGClothes()[id] << std::endl;
        }   
    }
    else {
        std::cout << "Current clothes - not set" << std::endl;
    }

    std::cout << std::endl;
}

void Story::_setName(std::string name)
{
    this->_name = name;
}

void Story::_setInfo(std::string info)
{
    this->_info = info;
}

void Story::_setAuthor(std::string author)
{
    this->_author = author;
}

void Story::_setDate(std::string date)
{
    this->_date = date;
}

bool Story::_isHeaderOkay(std::fstream* file)
{
    char header[0x13];
    file->read(header, 0x13);

    if (strcmp(header, "wewescriptcompiled") == 0) {
        return true;
    }

    return false;
}

bool Story::_isSizeOkay(std::fstream* file)
{
    file->seekg(0x14, std::ios::beg);
    uint32_t sizeFromFile;
    file->read(reinterpret_cast<char*>(&sizeFromFile), sizeof(uint32_t));
    
    file->seekg(0, std::ios::end);
    uint32_t realSize = file->tellg();

    file->seekg(0x18, std::ios::beg);

    if (realSize == sizeFromFile) {
        return true;
    }

    return false;
}

void Story::_loadGlobalInfo(std::fstream* file)
{
    uint32_t buff;
    uint16_t ffff = 0x0000;
    char buffString[0xff];
    this->_wipeStrBuff(buffString, 0xff);

    // read story name
    file->read(reinterpret_cast<char*>(&buff), sizeof(uint32_t));
    file->read(buffString, buff);
    this->_name = buffString;
    this->_wipeStrBuff(buffString);

    // read story info
    file->read(reinterpret_cast<char*>(&buff), sizeof(uint32_t));
    file->read(buffString, buff);
    this->_info = buffString;
    this->_wipeStrBuff(buffString);

    // read author
    file->read(reinterpret_cast<char*>(&buff), sizeof(uint32_t));
    file->read(buffString, buff);
    this->_author = buffString;
    this->_wipeStrBuff(buffString);

    // read date
    file->read(reinterpret_cast<char*>(&buff), sizeof(uint32_t));
    file->read(buffString, buff);
    this->_date = buffString;
    this->_wipeStrBuff(buffString);

    // check if end of global info
    file->read(reinterpret_cast<char*>(&ffff), sizeof(uint16_t));
    if (ffff != 0xffff) {
        std::cout << "0xffff is missing" << std::endl;
    }
}

void Story::_loadCharacters(std::fstream* file)
{
    // check if header is okay
    uint16_t header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(uint16_t));
    if (header != 0x0001) {
        std::cout << "character header error" << std::endl;
    }

    uint16_t numberOfCharacters = 0x0000;
    uint16_t buffId = 0x0000;
    uint16_t sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    std::vector<int> pathsId;
    uint16_t numberOfSpritesId = 0x0000;
    uint16_t spriteId = 0x0000;

    file->read(reinterpret_cast<char*>(&numberOfCharacters), sizeof(uint16_t));

    for (short i = 0; i < numberOfCharacters; i++) {
        pathsId.clear();
        file->read(reinterpret_cast<char*>(&buffId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(uint16_t));
        file->read(name, sizeOfName);
        strName = name;
        this->_wipeStrBuff(name);
        file->read(reinterpret_cast<char*>(&numberOfSpritesId), sizeof(uint16_t));
        for (short j = 0; j < numberOfSpritesId; j++) {
            file->read(reinterpret_cast<char*>(&spriteId), sizeof(uint16_t));
            pathsId.push_back((int)spriteId);
        }
        this->_Characters.push_back(Character(buffId, strName, pathsId));
    }
}

void Story::_loadCCE(std::fstream* file)
{
    // check if header is okay
    uint16_t header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(uint16_t));
    if (header != 0x0002) {
        std::cout << "CCE header error" << std::endl;
    }

    uint16_t numberOfCCE = 0x0000;
    uint16_t buffId = 0x0000;
    uint16_t sizeOfText = 0x0000;
    char text[0xff];
    this->_wipeStrBuff(text, 0xff);
    std::string strText;
    std::vector<std::vector<int>> clothesY;
    std::vector<int> clothesX;
    uint16_t sizeOfClothesY = 0x0000;
    uint16_t sizeOfClothesX = 0x0000;
    uint16_t pathId = 0x0000;
    uint16_t nextMessageId = 0x0000;

    file->read(reinterpret_cast<char*>(&numberOfCCE), sizeof(uint16_t));
    for (short i = 0; i < numberOfCCE; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&sizeOfText), sizeof(uint16_t));
        file->read(text, sizeOfText);
        strText = text;
        this->_wipeStrBuff(text);
        file->read(reinterpret_cast<char*>(&sizeOfClothesY), sizeof(uint16_t));
        for (short j = 0; j < sizeOfClothesY; j++) {
            file->read(reinterpret_cast<char*>(&sizeOfClothesX), sizeof(uint16_t));
            for (short k = 0; k < sizeOfClothesX; k++) {
                file->read(reinterpret_cast<char*>(&pathId), sizeof(uint16_t));
                clothesX.push_back((int)pathId);
            }
            clothesY.push_back(clothesX);
            clothesX.clear();
        }
        file->read(reinterpret_cast<char*>(&nextMessageId), sizeof(uint16_t));
        this->_CCEvents.push_back(ChooseClothesEvent(buffId, strText, clothesY, nextMessageId));
        clothesY.clear();
    }
}

void Story::_loadEvents(std::fstream* file)
{
    // check if header is okay
    uint16_t header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(uint16_t));
    if (header != 0x0003) {
        std::cout << "Event header error" << std::endl;
    }

    uint16_t numberOfEvents = 0x0000;
    uint16_t buffId = 0x0000;
    uint16_t numberOfPlayerOptions = 0x0000;
    uint16_t sizeOfPlayerOption = 0x0000;
    char playerOption[0xff];
    this->_wipeStrBuff(playerOption, 0xff);
    std::string strPlayerOption;
    std::vector<std::string> playerOptions;
    uint16_t numberOfNextMessages = 0x0000;
    uint16_t nextMessage = 0x0000;
    std::vector<int> nextMessages;
    uint16_t numberOfNextEvents = 0x0000;
    uint16_t nextEvent = 0x0000;
    std::vector<int> nextEvents;
    uint16_t mpei = 0x0000;
    uint16_t ccei = 0x0000;
    uint16_t show = 0x0000;

    file->read(reinterpret_cast<char*>(&numberOfEvents), sizeof(uint16_t));
    for (short i = 0; i < numberOfEvents; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&numberOfPlayerOptions), sizeof(uint16_t));
        for (short j = 0; j < numberOfPlayerOptions; j++) {
            file->read(reinterpret_cast<char*>(&sizeOfPlayerOption), sizeof(uint16_t));
            file->read(playerOption, sizeOfPlayerOption);
            strPlayerOption = playerOption;
            this->_wipeStrBuff(playerOption);
            playerOptions.push_back(strPlayerOption);
        }
        file->read(reinterpret_cast<char*>(&numberOfNextMessages), sizeof(uint16_t));
        for (short j = 0; j < numberOfNextMessages; j++) {
            file->read(reinterpret_cast<char*>(&nextMessage), sizeof(uint16_t));
            nextMessages.push_back(nextMessage);
        }
        file->read(reinterpret_cast<char*>(&numberOfNextEvents), sizeof(uint16_t));
        for (short j = 0; j < numberOfNextEvents; j++) {
            file->read(reinterpret_cast<char*>(&nextEvent), sizeof(uint16_t));
            nextEvents.push_back(nextEvent);
        }
        file->read(reinterpret_cast<char*>(&mpei), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&ccei), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&show), sizeof(uint16_t));

        this->_Events.push_back(Event(buffId, playerOptions, nextMessages, nextEvents, mpei, ccei, show));

        playerOptions.clear();
        nextMessages.clear();
        nextEvents.clear();
    }
}

void Story::_loadImages(std::fstream* file)
{
    // check if header is okay
    uint16_t header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(uint16_t));
    if (header != 0x0004) {
        std::cout << "Image header error" << std::endl;
    }

    uint16_t numberOfImages = 0x0000;
    uint16_t buffId = 0x0000;
    uint16_t sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    uint16_t sizeOfPath = 0x0000;
    char path[0xff];
    this->_wipeStrBuff(path, 0xff);
    std::string strPath;

    file->read(reinterpret_cast<char*>(&numberOfImages), sizeof(uint16_t));
    for (short i = 0; i < numberOfImages; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(uint16_t));
        file->read(name, sizeOfName);
        strName = name;
        this->_wipeStrBuff(name);
        file->read(reinterpret_cast<char*>(&sizeOfPath), sizeof(uint16_t));
        file->read(path, sizeOfPath);
        strPath = path;
        this->_wipeStrBuff(path);
        this->_Images.push_back(Image(buffId, strName, strPath));
    }
}

void Story::_loadMPE(std::fstream* file)
{
    // check if header is okay
    uint16_t header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(uint16_t));
    if (header != 0x0005) {
        std::cout << "MPE header error" << std::endl;
    }

    uint16_t sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    uint16_t sizeOfText = 0x0000;
    char text[0xff];
    this->_wipeStrBuff(text, 0xff);
    std::string strText;

    uint16_t sizeOfFacesY = 0x0000;
    uint16_t sizeOfFacesX = 0x0000;
    uint16_t face = 0x0000;
    std::vector<std::vector<int>> facesY;
    std::vector<int> facesX;

    uint16_t sizeOfSkinsY = 0x0000;
    uint16_t sizeOfSkinsX = 0x0000;
    uint16_t skin = 0x0000;
    std::vector<std::vector<int>> skinsY;
    std::vector<int> skinsX;

    uint16_t sizeOfHairsY = 0x0000;
    uint16_t sizeOfHairsX = 0x0000;
    uint16_t hair = 0x0000;
    std::vector<std::vector<int>> hairsY;
    std::vector<int> hairsX;

    uint16_t nextMessageId = 0x0000;

    file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(uint16_t));
    file->read(name, sizeOfName);
    strName = name;
    file->read(reinterpret_cast<char*>(&sizeOfText), sizeof(uint16_t));
    file->read(text, sizeOfText);
    strText = text;

    file->read(reinterpret_cast<char*>(&sizeOfFacesY), sizeof(uint16_t));
    for (short y = 0; y < sizeOfFacesY; y++) {
        file->read(reinterpret_cast<char*>(&sizeOfFacesX), sizeof(uint16_t));
        for (short x = 0; x < sizeOfFacesX; x++) {
            file->read(reinterpret_cast<char*>(&face), sizeof(uint16_t));
            facesX.push_back(face);
        }
        facesY.push_back(facesX);
        facesX.clear();
    }

    file->read(reinterpret_cast<char*>(&sizeOfSkinsY), sizeof(uint16_t));
    for (short y = 0; y < sizeOfSkinsY; y++) {
        file->read(reinterpret_cast<char*>(&sizeOfSkinsX), sizeof(uint16_t));
        for (short x = 0; x < sizeOfSkinsX; x++) {
            file->read(reinterpret_cast<char*>(&skin), sizeof(uint16_t));
            skinsX.push_back(skin);
        }
        skinsY.push_back(skinsX);
        skinsX.clear();
    }

    file->read(reinterpret_cast<char*>(&sizeOfHairsY), sizeof(uint16_t));
    for (short y = 0; y < sizeOfHairsY; y++) {
        file->read(reinterpret_cast<char*>(&sizeOfHairsX), sizeof(uint16_t));
        for (short x = 0; x < sizeOfHairsX; x++) {
            file->read(reinterpret_cast<char*>(&hair), sizeof(uint16_t));
            hairsX.push_back(hair);
        }
        hairsY.push_back(hairsX);
        hairsX.clear();
    }

    file->read(reinterpret_cast<char*>(&nextMessageId), sizeof(uint16_t));

    this->_MPEvent = new MakeProtagonistEvent(strName, strText, facesY, skinsY, hairsY, nextMessageId);
}

void Story::_loadMessages(std::fstream* file)
{
    // check if header is okay
    uint16_t header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(uint16_t));
    if (header != 0x0006) {
        std::cout << "Message header error" << std::endl;
    }

    uint16_t numberOfMessages = 0x0000;
    uint16_t buffId = 0x0000;
    uint16_t characterId = 0x0000;
    uint16_t sizeOfText = 0x0000;
    char text[0xff];
    this->_wipeStrBuff(text, 0xff);
    std::string strText;
    uint16_t numberOfMusicsId = 0x0000;
    uint16_t musicId = 0x0000;
    std::vector<int> musics;
    uint16_t numberOfSfxId = 0x0000;
    uint16_t sfxId = 0x0000;
    std::vector<int> sfxs;
    uint16_t spriteId = 0x0000;
    uint16_t animationId = 0x0000;
    uint16_t clothesId = 0x0000;
    uint16_t bgImageId = 0x0000;
    uint16_t nextMessageId = 0x0000;
    uint16_t nextEventId = 0x0000;
    uint16_t messageX = 0x0000;
    uint16_t messageY = 0x0000;
    uint16_t characterX = 0x0000;
    uint16_t characterY = 0x0000;

    file->read(reinterpret_cast<char*>(&numberOfMessages), sizeof(uint16_t));
    for (short i = 0; i < numberOfMessages; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&characterId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&sizeOfText), sizeof(uint16_t));
        file->read(text, sizeOfText);
        strText = text;
        this->_wipeStrBuff(text);
        file->read(reinterpret_cast<char*>(&numberOfMusicsId), sizeof(uint16_t));
        for (short j = 0; j < numberOfMusicsId; j++) {
            file->read(reinterpret_cast<char*>(&musicId), sizeof(uint16_t));
            musics.push_back(musicId);
        }
        file->read(reinterpret_cast<char*>(&numberOfSfxId), sizeof(uint16_t));
        for (short j = 0; j < numberOfSfxId; j++) {
            file->read(reinterpret_cast<char*>(&sfxId), sizeof(uint16_t));
            sfxs.push_back(sfxId);
        }
        file->read(reinterpret_cast<char*>(&spriteId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&animationId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&clothesId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&bgImageId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&nextMessageId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&nextEventId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&messageX), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&messageY), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&characterX), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&characterY), sizeof(uint16_t));

        this->_Messages.push_back(Message(buffId, characterId, strText, musics, sfxs, spriteId, 
            animationId, clothesId, bgImageId, nextMessageId, nextEventId, messageX, messageY,
            characterX, characterY));

        musics.clear();
        sfxs.clear();
    }
}

void Story::_loadMusics(std::fstream* file)
{
    // check if header is okay
    uint16_t header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(uint16_t));
    if (header != 0x0007) {
        std::cout << "Music header error" << std::endl;
    }

    uint16_t numberOfMusics = 0x0000;
    uint16_t buffId = 0x0000;
    uint16_t sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    uint16_t sizeOfPath = 0x0000;
    char path[0xff];
    this->_wipeStrBuff(path, 0xff);
    std::string strPath;

    file->read(reinterpret_cast<char*>(&numberOfMusics), sizeof(uint16_t));
    for (short i = 0; i < numberOfMusics; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(uint16_t));
        file->read(name, sizeOfName);
        strName = name;
        this->_wipeStrBuff(name);
        file->read(reinterpret_cast<char*>(&sizeOfPath), sizeof(uint16_t));
        file->read(path, sizeOfPath);
        strPath = path;
        this->_wipeStrBuff(path);

        this->_Musics.push_back(Music(buffId, strName, strPath));
    }
}

void Story::_loadSfxs(std::fstream* file)
{
    // check if header is okay
    uint16_t header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(uint16_t));
    if (header != 0x0008) {
        std::cout << "Sfx header error" << std::endl;
    }

    uint16_t numberOfSfxs = 0x0000;
    uint16_t buffId = 0x0000;
    uint16_t sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    uint16_t sizeOfPath = 0x0000;
    char path[0xff];
    this->_wipeStrBuff(path, 0xff);
    std::string strPath;

    file->read(reinterpret_cast<char*>(&numberOfSfxs), sizeof(uint16_t));
    for (short i = 0; i < numberOfSfxs; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(uint16_t));
        file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(uint16_t));
        file->read(name, sizeOfName);
        strName = name;
        this->_wipeStrBuff(name);
        file->read(reinterpret_cast<char*>(&sizeOfPath), sizeof(uint16_t));
        file->read(path, sizeOfPath);
        strPath = path;
        this->_wipeStrBuff(path);

        this->_Sfxs.push_back(Sfx(buffId, strName, strPath));
    }
}

void Story::_loadCompilationInfo(std::fstream* file)
{
    unsigned char buff = 0x00;
    std::string compilationInfo;

    while (buff != 0xff) {
        file->read(reinterpret_cast<char*>(&buff), sizeof(char));
        if (buff != 0xff) {
            compilationInfo += buff;
        }
    }

    file->read(reinterpret_cast<char*>(&buff), sizeof(char));
    if (buff != 0x00) {
        std::cout << "end of info error" << std::endl;
    }

    this->_compilationInfo = compilationInfo;

    std::cout << std::endl;
    std::cout << "compilation info: " << std::endl;
    std::cout << compilationInfo << "\n\n";
}

bool Story::_checkEndOfFile(std::fstream* file)
{
    unsigned char buff = 0x00;
    file->read(reinterpret_cast<char*>(&buff), sizeof(char));
    if (buff != 0xff) {
        std::cout << "0xff is missing at the end of file" << std::endl;
        return false;
    }
    file->read(reinterpret_cast<char*>(&buff), sizeof(char));
    if (buff != 0x00) {
        std::cout << "0x00 is missing at the end of file" << std::endl;
        return false;
    }
    file->read(reinterpret_cast<char*>(&buff), sizeof(char));
    if (file->eof()) {
        return true;
    }
    return false;
}

void Story::_swapBytes(int& x)
{
    x = ((x & 0x00FF) << 16) | ((x & 0xFF0000) >> 16) | (x & 0x0000FF00);
    x = ((x & 0xFF00FF00) >> 8) | ((x & 0x00FF00FF) << 8);
}

void Story::_wipeStrBuff(char* buff)
{
    int i = 0;
    while (buff[i] != NULL) {
        buff[i] = NULL;
        i++;
    }

}

void Story::_wipeStrBuff(char* buff, int size)
{
    memset(buff, 0, size);
}
