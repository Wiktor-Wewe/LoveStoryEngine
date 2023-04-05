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
    short buff;

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
    return NULL;
}

Message* Story::_findMessageById(int id)
{
    for (int i = 0; i < this->_Messages.size(); i++) {
        if (this->_Messages[i].getId() == id) {
            return &this->_Messages[i];
        }
    }
    return NULL;
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
    return NULL;
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
    std::cout << "clothes id: " << m->getClothesId() << std::endl;
    std::cout << "bg image id: " << m->getBgImageId() << std::endl;
    std::cout << "next message id: " << m->getNextMessage() << std::endl;
    std::cout << "next event id: " << m->getNextEvent() << std::endl;
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
    std::cout << std::endl;
    std::cout << "Take your time and choose: " << std::endl;
    for (int i = 0; i < e->getPlayerOptions().size(); i++) {
        std::cout << "[" << i << "] " << e->getPlayerOptions()[i] << std::endl;
    }
    std::cout << std::endl;
}

void Story::_showMPE(MakeProtagonistEvent* mpe)
{
    std::cout << "id: " << mpe->getId() << std::endl;
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

    this->_getPlayer()->printInfoAboutPlayer();
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

    for (int i = 0; i < cce->getClothes()[playerInput].size(); i++) {
        std::cout << "[" << i << "] " << cce->getClothes()[playerInput][i] << std::endl;
    }
    std::cin >> playerInput;
    this->_getPlayer()->setCurrentClothesId(playerInput);

    std::cout << "Player clothes: " << this->_getPlayer()->getCurrentClothes() << std::endl;
    system("pause");
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
    int sizeFromFile;
    file->read(reinterpret_cast<char*>(&sizeFromFile), sizeof(int));
    this->_swapBytes(sizeFromFile);

    file->seekg(0, std::ios::end);
    int realSize = file->tellg();

    file->seekg(0x18, std::ios::beg);

    if (realSize == sizeFromFile) {
        return true;
    }

    return false;
}

void Story::_loadGlobalInfo(std::fstream* file)
{
    int buff;
    unsigned short ffff = 0x0000;
    char buffString[0xff];
    this->_wipeStrBuff(buffString, 0xff);

    // read story name
    file->read(reinterpret_cast<char*>(&buff), sizeof(int));
    file->read(buffString, buff);
    this->_name = buffString;
    this->_wipeStrBuff(buffString);

    // read story info
    file->read(reinterpret_cast<char*>(&buff), sizeof(int));
    file->read(buffString, buff);
    this->_info = buffString;
    this->_wipeStrBuff(buffString);

    // read author
    file->read(reinterpret_cast<char*>(&buff), sizeof(int));
    file->read(buffString, buff);
    this->_author = buffString;
    this->_wipeStrBuff(buffString);

    // read date
    file->read(reinterpret_cast<char*>(&buff), sizeof(int));
    file->read(buffString, buff);
    this->_date = buffString;
    this->_wipeStrBuff(buffString);

    // check if end of global info
    file->read(reinterpret_cast<char*>(&ffff), sizeof(short));
    if (ffff != 0xffff) {
        std::cout << "0xffff is missing" << std::endl;
    }
}

void Story::_loadCharacters(std::fstream* file)
{
    // check if header is okay
    unsigned short header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(short));
    if (header != 0x0001) {
        std::cout << "character header error" << std::endl;
    }

    unsigned short numberOfCharacters = 0x0000;
    unsigned short buffId = 0x0000;
    unsigned short sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    std::vector<std::string> paths;
    unsigned short numberOfSpritesPaths = 0x0000;
    unsigned short sizeOfPath = 0x0000;
    char path[0xff];
    this->_wipeStrBuff(path, 0xff);
    std::string strPath;

    file->read(reinterpret_cast<char*>(&numberOfCharacters), sizeof(short));

    for (short i = 0; i < numberOfCharacters; i++) {
        paths.clear();
        file->read(reinterpret_cast<char*>(&buffId), sizeof(short));
        file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(short));
        file->read(name, sizeOfName);
        strName = name;
        this->_wipeStrBuff(name);
        file->read(reinterpret_cast<char*>(&numberOfSpritesPaths), sizeof(short));
        for (short j = 0; j < numberOfSpritesPaths; j++) {
            file->read(reinterpret_cast<char*>(&sizeOfPath), sizeof(short));
            file->read(path, sizeOfPath);
            strPath = path;
            this->_wipeStrBuff(path);
            paths.push_back(strPath);
        }
        this->_Characters.push_back(Character(buffId, strName, paths));
    }
}

void Story::_loadCCE(std::fstream* file)
{
    // check if header is okay
    unsigned short header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(short));
    if (header != 0x0002) {
        std::cout << "CCE header error" << std::endl;
    }

    unsigned short numberOfCCE = 0x0000;
    unsigned short buffId = 0x0000;
    unsigned short sizeOfText = 0x0000;
    char text[0xff];
    this->_wipeStrBuff(text, 0xff);
    std::string strText;
    std::vector<std::vector<std::string>> clothesY;
    std::vector<std::string> clothesX;
    unsigned short sizeOfClothesY = 0x0000;
    unsigned short sizeOfClothesX = 0x0000;
    unsigned short sizeOfPath = 0x0000;
    char path[0xff];
    this->_wipeStrBuff(path, 0xff);
    std::string strPath;
    unsigned short nextMessageId = 0x0000;

    file->read(reinterpret_cast<char*>(&numberOfCCE), sizeof(short));
    for (short i = 0; i < numberOfCCE; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(short));
        file->read(reinterpret_cast<char*>(&sizeOfText), sizeof(short));
        file->read(text, sizeOfText);
        strText = text;
        this->_wipeStrBuff(text);
        file->read(reinterpret_cast<char*>(&sizeOfClothesY), sizeof(short));
        for (short j = 0; j < sizeOfClothesY; j++) {
            file->read(reinterpret_cast<char*>(&sizeOfClothesX), sizeof(short));
            for (short k = 0; k < sizeOfClothesX; k++) {
                file->read(reinterpret_cast<char*>(&sizeOfPath), sizeof(short));
                file->read(path, sizeOfPath);
                strPath = path;
                this->_wipeStrBuff(path);
                clothesX.push_back(strPath);
            }
            clothesY.push_back(clothesX);
            clothesX.clear();
        }
        file->read(reinterpret_cast<char*>(&nextMessageId), sizeof(short));
        this->_CCEvents.push_back(ChooseClothesEvent(buffId, strText, clothesY, nextMessageId));
        clothesY.clear();
    }
}

void Story::_loadEvents(std::fstream* file)
{
    // check if header is okay
    unsigned short header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(short));
    if (header != 0x0003) {
        std::cout << "Event header error" << std::endl;
    }

    unsigned short numberOfEvents = 0x0000;
    unsigned short buffId = 0x0000;
    unsigned short numberOfPlayerOptions = 0x0000;
    unsigned short sizeOfPlayerOption = 0x0000;
    char playerOption[0xff];
    this->_wipeStrBuff(playerOption, 0xff);
    std::string strPlayerOption;
    std::vector<std::string> playerOptions;
    unsigned short numberOfNextMessages = 0x0000;
    unsigned short nextMessage = 0x0000;
    std::vector<int> nextMessages;
    unsigned short numberOfNextEvents = 0x0000;
    unsigned short nextEvent = 0x0000;
    std::vector<int> nextEvents;
    unsigned short mpei = 0x0000;
    unsigned short ccei = 0x0000;

    file->read(reinterpret_cast<char*>(&numberOfEvents), sizeof(short));
    for (short i = 0; i < numberOfEvents; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(short));
        file->read(reinterpret_cast<char*>(&numberOfPlayerOptions), sizeof(short));
        for (short j = 0; j < numberOfPlayerOptions; j++) {
            file->read(reinterpret_cast<char*>(&sizeOfPlayerOption), sizeof(short));
            file->read(playerOption, sizeOfPlayerOption);
            strPlayerOption = playerOption;
            this->_wipeStrBuff(playerOption);
            playerOptions.push_back(strPlayerOption);
        }
        file->read(reinterpret_cast<char*>(&numberOfNextMessages), sizeof(short));
        for (short j = 0; j < numberOfNextMessages; j++) {
            file->read(reinterpret_cast<char*>(&nextMessage), sizeof(short));
            nextMessages.push_back(nextMessage);
        }
        file->read(reinterpret_cast<char*>(&numberOfNextEvents), sizeof(short));
        for (short j = 0; j < numberOfNextEvents; j++) {
            file->read(reinterpret_cast<char*>(&nextEvent), sizeof(short));
            nextEvents.push_back(nextEvent);
        }
        file->read(reinterpret_cast<char*>(&mpei), sizeof(short));
        file->read(reinterpret_cast<char*>(&ccei), sizeof(short));

        this->_Events.push_back(Event(buffId, playerOptions, nextMessages, nextEvents, mpei, ccei));

        playerOptions.clear();
        nextMessages.clear();
        nextEvents.clear();
    }
}

void Story::_loadImages(std::fstream* file)
{
    // check if header is okay
    unsigned short header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(short));
    if (header != 0x0004) {
        std::cout << "Image header error" << std::endl;
    }

    unsigned short numberOfImages = 0x0000;
    unsigned short buffId = 0x0000;
    unsigned short sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    unsigned short sizeOfPath = 0x0000;
    char path[0xff];
    this->_wipeStrBuff(path, 0xff);
    std::string strPath;

    file->read(reinterpret_cast<char*>(&numberOfImages), sizeof(short));
    for (short i = 0; i < numberOfImages; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(short));
        file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(short));
        file->read(name, sizeOfName);
        strName = name;
        this->_wipeStrBuff(name);
        file->read(reinterpret_cast<char*>(&sizeOfPath), sizeof(short));
        file->read(path, sizeOfPath);
        strPath = path;
        this->_wipeStrBuff(path);
        this->_Images.push_back(Image(buffId, strName, strPath));
    }
}

void Story::_loadMPE(std::fstream* file)
{
    // check if header is okay
    unsigned short header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(short));
    if (header != 0x0005) {
        std::cout << "MPE header error" << std::endl;
    }

    unsigned short buffId = 0x0000;
    unsigned short sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    unsigned short sizeOfText = 0x0000;
    char text[0xff];
    this->_wipeStrBuff(text, 0xff);
    std::string strText;

    unsigned short sizeOfFacesY = 0x0000;
    unsigned short sizeOfFacesX = 0x0000;
    unsigned short sizeOfFace = 0x0000;
    char face[0xff];
    this->_wipeStrBuff(face, 0xff);
    std::string strFace;
    std::vector<std::vector<std::string>> facesY;
    std::vector<std::string> facesX;

    unsigned short sizeOfSkinsY = 0x0000;
    unsigned short sizeOfSkinsX = 0x0000;
    unsigned short sizeOfSkin = 0x0000;
    char skin[0xff];
    this->_wipeStrBuff(skin, 0xff);
    std::string strSkin;
    std::vector<std::vector<std::string>> skinsY;
    std::vector<std::string> skinsX;

    unsigned short sizeOfHairsY = 0x0000;
    unsigned short sizeOfHairsX = 0x0000;
    unsigned short sizeOfHair = 0x0000;
    char hair[0xff];
    this->_wipeStrBuff(hair, 0xff);
    std::string strHair;
    std::vector<std::vector<std::string>> hairsY;
    std::vector<std::string> hairsX;

    unsigned short nextMessageId = 0x0000;

    file->read(reinterpret_cast<char*>(&buffId), sizeof(short));
    file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(short));
    file->read(name, sizeOfName);
    strName = name;
    file->read(reinterpret_cast<char*>(&sizeOfText), sizeof(short));
    file->read(text, sizeOfText);
    strText = text;

    file->read(reinterpret_cast<char*>(&sizeOfFacesY), sizeof(short));
    for (short y = 0; y < sizeOfFacesY; y++) {
        file->read(reinterpret_cast<char*>(&sizeOfFacesX), sizeof(short));
        for (short x = 0; x < sizeOfFacesX; x++) {
            file->read(reinterpret_cast<char*>(&sizeOfFace), sizeof(short));
            file->read(face, sizeOfFace);
            strFace = face;
            this->_wipeStrBuff(face);
            facesX.push_back(strFace);
        }
        facesY.push_back(facesX);
        facesX.clear();
    }

    file->read(reinterpret_cast<char*>(&sizeOfSkinsY), sizeof(short));
    for (short y = 0; y < sizeOfSkinsY; y++) {
        file->read(reinterpret_cast<char*>(&sizeOfSkinsX), sizeof(short));
        for (short x = 0; x < sizeOfSkinsX; x++) {
            file->read(reinterpret_cast<char*>(&sizeOfSkin), sizeof(short));
            file->read(skin, sizeOfSkin);
            strSkin = skin;
            this->_wipeStrBuff(skin);
            skinsX.push_back(strSkin);
        }
        skinsY.push_back(skinsX);
        skinsX.clear();
    }

    file->read(reinterpret_cast<char*>(&sizeOfHairsY), sizeof(short));
    for (short y = 0; y < sizeOfHairsY; y++) {
        file->read(reinterpret_cast<char*>(&sizeOfHairsX), sizeof(short));
        for (short x = 0; x < sizeOfHairsX; x++) {
            file->read(reinterpret_cast<char*>(&sizeOfHair), sizeof(short));
            file->read(hair, sizeOfHair);
            strHair = hair;
            this->_wipeStrBuff(hair);
            hairsX.push_back(strHair);
        }
        hairsY.push_back(hairsX);
        hairsX.clear();
    }

    file->read(reinterpret_cast<char*>(&nextMessageId), sizeof(short));

    this->_MPEvent = new MakeProtagonistEvent(buffId, strName, strText, facesY, skinsY, hairsY, nextMessageId);
}

void Story::_loadMessages(std::fstream* file)
{
    // check if header is okay
    unsigned short header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(short));
    if (header != 0x0006) {
        std::cout << "Message header error" << std::endl;
    }

    unsigned short numberOfMessages = 0x0000;
    unsigned short buffId = 0x0000;
    unsigned short sizeOfText = 0x0000;
    char text[0xff];
    this->_wipeStrBuff(text, 0xff);
    std::string strText;
    unsigned short numberOfMusicsId = 0x0000;
    unsigned short musicId = 0x0000;
    std::vector<int> musics;
    unsigned short numberOfSfxId = 0x0000;
    unsigned short sfxId = 0x0000;
    std::vector<int> sfxs;
    unsigned short spriteId = 0x0000;
    unsigned short clothesId = 0x0000;
    unsigned short bgImageId = 0x0000;
    unsigned short nextMessageId = 0x0000;
    unsigned short nextEventId = 0x0000;

    file->read(reinterpret_cast<char*>(&numberOfMessages), sizeof(short));
    for (short i = 0; i < numberOfMessages; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(short));
        file->read(reinterpret_cast<char*>(&sizeOfText), sizeof(short));
        file->read(text, sizeOfText);
        strText = text;
        this->_wipeStrBuff(text);
        file->read(reinterpret_cast<char*>(&numberOfMusicsId), sizeof(short));
        for (short j = 0; j < numberOfMusicsId; j++) {
            file->read(reinterpret_cast<char*>(&musicId), sizeof(short));
            musics.push_back(musicId);
        }
        file->read(reinterpret_cast<char*>(&numberOfSfxId), sizeof(short));
        for (short j = 0; j < numberOfSfxId; j++) {
            file->read(reinterpret_cast<char*>(&sfxId), sizeof(short));
            sfxs.push_back(sfxId);
        }
        file->read(reinterpret_cast<char*>(&spriteId), sizeof(short));
        file->read(reinterpret_cast<char*>(&clothesId), sizeof(short));
        file->read(reinterpret_cast<char*>(&bgImageId), sizeof(short));
        file->read(reinterpret_cast<char*>(&nextMessageId), sizeof(short));
        file->read(reinterpret_cast<char*>(&nextEventId), sizeof(short));

        this->_Messages.push_back(Message(buffId, strText, musics, sfxs, spriteId, clothesId, bgImageId, nextMessageId, nextEventId));

        musics.clear();
        sfxs.clear();
    }
}

void Story::_loadMusics(std::fstream* file)
{
    // check if header is okay
    unsigned short header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(short));
    if (header != 0x0007) {
        std::cout << "Music header error" << std::endl;
    }

    unsigned short numberOfMusics = 0x0000;
    unsigned short buffId = 0x0000;
    unsigned short sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    unsigned short sizeOfPath = 0x0000;
    char path[0xff];
    this->_wipeStrBuff(path, 0xff);
    std::string strPath;

    file->read(reinterpret_cast<char*>(&numberOfMusics), sizeof(short));
    for (short i = 0; i < numberOfMusics; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(short));
        file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(short));
        file->read(name, sizeOfName);
        strName = name;
        this->_wipeStrBuff(name);
        file->read(reinterpret_cast<char*>(&sizeOfPath), sizeof(short));
        file->read(path, sizeOfPath);
        strPath = path;
        this->_wipeStrBuff(path);

        this->_Musics.push_back(Music(buffId, strName, strPath));
    }
}

void Story::_loadSfxs(std::fstream* file)
{
    // check if header is okay
    unsigned short header = 0x0000;
    file->read(reinterpret_cast<char*>(&header), sizeof(short));
    if (header != 0x0008) {
        std::cout << "Sfx header error" << std::endl;
    }

    unsigned short numberOfSfxs = 0x0000;
    unsigned short buffId = 0x0000;
    unsigned short sizeOfName = 0x0000;
    char name[0xff];
    this->_wipeStrBuff(name, 0xff);
    std::string strName;
    unsigned short sizeOfPath = 0x0000;
    char path[0xff];
    this->_wipeStrBuff(path, 0xff);
    std::string strPath;

    file->read(reinterpret_cast<char*>(&numberOfSfxs), sizeof(short));
    for (short i = 0; i < numberOfSfxs; i++) {
        file->read(reinterpret_cast<char*>(&buffId), sizeof(short));
        file->read(reinterpret_cast<char*>(&sizeOfName), sizeof(short));
        file->read(name, sizeOfName);
        strName = name;
        this->_wipeStrBuff(name);
        file->read(reinterpret_cast<char*>(&sizeOfPath), sizeof(short));
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
