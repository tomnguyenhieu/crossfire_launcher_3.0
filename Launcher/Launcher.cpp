#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>

#include "LoginPage.h"
#include "BackgroundManager.h"
#include "TextManager.h"
#include "Logo.h"
#include "TopMenu.h"
#include "FooterMenu.h"
#include "RightPanel.h"
#include "LeftPanel.h"
#include "CharacterLobbyDisplay.h"
#include "CharacterTitleBG.h"
#include "TeamLobbyDisplaySelect.h"

const int WIDTH = 1600;
const int HEIGHT = 900;

enum class AppState { LOGIN, LOADING, LOBBY };
AppState currentState = AppState::LOADING;

void startGame() {
    std::string gamePath = "C:/Users/tomng/Desktop/CSA/cstrike.exe";
    std::system(gamePath.c_str());
}

// Hàm để load background texture ngẫu nhiên
sf::Texture loadRandomBackgroundTexture() {
    sf::Texture texture;

    // Khởi tạo số ngẫu nhiên
    std::srand(static_cast<unsigned>(std::time(nullptr)));  // Seed với thời gian hiện tại

    // Sinh số ngẫu nhiên từ 0 đến 13
    int randomIndex = std::rand() % 14;  // 14 là số lượng hình ảnh từ 00 đến 13

    // Tạo tên file dựa trên số ngẫu nhiên
    std::ostringstream fileNameStream;
    fileNameStream << "../Texture/LobbyBG/LobbyBG" << std::setw(2) << std::setfill('0') << randomIndex << ".PNG";
    std::string fileName = fileNameStream.str();

    // Load texture từ file
    if (!texture.loadFromFile(fileName)) {
        throw std::runtime_error("Failed to load texture from " + fileName);
    }

    return texture;
}

int main()
{
    std::cout << "Launcher Crossfire Beta Test Made By @CKVN" << std::endl;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CROSSFIRE LAUNCHER 3.0 BY @CKVN", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(false);

    // font
    sf::Font mainFont;
    if (!mainFont.loadFromFile("../Fonts/arial.ttf"))
    {
        return -1;
    }

    // clock
    sf::Clock deltaClock;
    float countdownTime = 2.8f;
    bool actionExecuted = false;

    // check save password 
    bool isSavePasswordEnabled = false;

    // Biến để theo dõi trạng thái của các nút
    bool playBtnClicked = false;
    bool bagBtnClicked = false;
    bool gachaBtnClicked = false;
    bool shopBtnClicked = false;

    // LOADING SCREEN
    // loading screen
    sf::Texture loadingScreen_Texture;
    loadingScreen_Texture.loadFromFile("../Texture/LoadingScreen/LoadingScreen.PNG");
    BackgroundManager loadingScreen(loadingScreen_Texture, sf::Vector2f(0, 0));

    // loading screen text;
    TextManager loadingScreenText(mainFont, "Loading Launcher...", 16, sf::Color::White, sf::Vector2f(WIDTH-260, HEIGHT - 100));


    // LOGIN SCREEN
    // login background
    sf::Texture loginBG_Texture;
    loginBG_Texture.loadFromFile("../Texture/LoginScreen/LoginScreenBG.PNG");
    BackgroundManager loginBG(loginBG_Texture, sf::Vector2f(0, 0));

    // login box
    sf::Texture loginBoxBG_Texture;
    loginBoxBG_Texture.loadFromFile("../Texture/LoginScreen/LoginBg.PNG");
    LoginPage loginBoxBG(loginBoxBG_Texture, sf::Vector2f(1024, 641));

    sf::Texture loginBtn_Up_Texture;
    sf::Texture loginBtn_Focus_Texture;
    loginBtn_Up_Texture.loadFromFile("../Texture/LoginScreen/LoginBTN_Up.PNG");
    loginBtn_Focus_Texture.loadFromFile("../Texture/LoginScreen/LoginBTN_Focus.PNG");
    LoginPage loginBtn(loginBtn_Up_Texture, sf::Vector2f(1333, 666));

    sf::Texture loginInputName_Texture;
    loginInputName_Texture.loadFromFile("../Texture/LoginScreen/InputName.PNG");
    LoginPage loginInputName(loginInputName_Texture, sf::Vector2f(1049, 668));

    sf::Texture loginInputPassword_Texture;
    loginInputPassword_Texture.loadFromFile("../Texture/LoginScreen/InputPassword.PNG");
    LoginPage loginInputPassword(loginInputPassword_Texture, sf::Vector2f(1049, 705));

    sf::Texture loginSavePasswordBtn_Off_Texture;
    sf::Texture loginSavePasswordBtn_On_Texture;
    loginSavePasswordBtn_Off_Texture.loadFromFile("../Texture/LoginScreen/SaveButtonOff.PNG");
    loginSavePasswordBtn_On_Texture.loadFromFile("../Texture/LoginScreen/SaveButtonOn.PNG");
    LoginPage loginSavePasswordBtn(loginSavePasswordBtn_Off_Texture, sf::Vector2f(1050, 747));

    sf::Texture loginCreateAccBtn_Texture;
    loginCreateAccBtn_Texture.loadFromFile("../Texture/LoginScreen/CreateAccount.PNG");
    LoginPage loginCreateAccBtn(loginCreateAccBtn_Texture, sf::Vector2f(1299, 792));

    sf::Texture loginFindPassBtn_Texture;
    loginFindPassBtn_Texture.loadFromFile("../Texture/LoginScreen/FindPassword.PNG");
    LoginPage loginFindPassBtn(loginFindPassBtn_Texture, sf::Vector2f(1187, 747));

    sf::Texture loginExitBtn_Texture;
    loginExitBtn_Texture.loadFromFile("../Texture/LoginScreen/Exit.PNG");
    LoginPage loginExitBtn(loginExitBtn_Texture, sf::Vector2f(1496, 792)); 

    // Account & Password logging name
    TextManager accLogginName(mainFont, "CKVN", 16, sf::Color::White, sf::Vector2f(1049 + 10, 668 + 4));
    TextManager accLogginPass(mainFont, "**************", 16, sf::Color::White, sf::Vector2f(1049 + 10, 705 + 8));


    // LOBBY
    // background
    sf::Texture mainMenuBG_Texture;
    try {
        mainMenuBG_Texture = loadRandomBackgroundTexture();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    // Sử dụng texture để tạo BackgroundManager (giả định bạn có lớp BackgroundManager)
    BackgroundManager mainMenuBG(mainMenuBG_Texture, sf::Vector2f(0, 0));

    // logo
    sf::Texture logoSprSheet;
    logoSprSheet.loadFromFile("../Texture/Sprite/BL_FX.png");
    Logo logoSpr(logoSprSheet, sf::Vector2f(10, -9));

    // top menu background
    sf::Texture topMenuBg_Texture;
    topMenuBg_Texture.loadFromFile("../Texture/TopMenu/TopMenuBG.PNG");
    TopMenu topMenuBg(topMenuBg_Texture, sf::Vector2f(0, 0));

    // top menu button left
    sf::Texture topMenuBtnPlay_Down_Texture;
    sf::Texture topMenuBtnPlay_Up_Texture;
    sf::Texture topMenuBtnPlay_Focus_Texture;
    topMenuBtnPlay_Down_Texture.loadFromFile("../Texture/TopMenu/Play_Down.PNG");
    topMenuBtnPlay_Up_Texture.loadFromFile("../Texture/TopMenu/Play_Up.PNG");
    topMenuBtnPlay_Focus_Texture.loadFromFile("../Texture/TopMenu/Play_Focus.PNG");
    TopMenu topMenuBtnPlay(topMenuBtnPlay_Down_Texture, sf::Vector2f(214, 2.5));

    sf::Texture topMenuBtnBag_Down_Texture;
    sf::Texture topMenuBtnBag_Up_Texture;
    sf::Texture topMenuBtnBag_Focus_Texture;
    topMenuBtnBag_Down_Texture.loadFromFile("../Texture/TopMenu/Inven_Down.PNG");
    topMenuBtnBag_Up_Texture.loadFromFile("../Texture/TopMenu/Inven_Up.PNG");
    topMenuBtnBag_Focus_Texture.loadFromFile("../Texture/TopMenu/Inven_Focus.PNG");
    TopMenu topMenuBtnBag(topMenuBtnBag_Up_Texture, sf::Vector2f(214 + 190 - 36, 2.5));

    sf::Texture topMenuBtnGacha_Down_Texture;
    sf::Texture topMenuBtnGacha_Up_Texture;
    sf::Texture topMenuBtnGacha_Focus_Texture;
    topMenuBtnGacha_Down_Texture.loadFromFile("../Texture/TopMenu/GachaShop_Down.PNG");
    topMenuBtnGacha_Up_Texture.loadFromFile("../Texture/TopMenu/GachaShop_Up.PNG");
    topMenuBtnGacha_Focus_Texture.loadFromFile("../Texture/TopMenu/GachaShop_Focus.PNG");
    TopMenu topMenuBtnGacha(topMenuBtnGacha_Up_Texture, sf::Vector2f(214 + (190 - 36) * 2, 2.5));

    sf::Texture topMenuBtnShop_Down_Texture;
    sf::Texture topMenuBtnShop_Up_Texture;
    sf::Texture topMenuBtnShop_Focus_Texture;
    topMenuBtnShop_Down_Texture.loadFromFile("../Texture/TopMenu/Shop_Down.PNG");
    topMenuBtnShop_Up_Texture.loadFromFile("../Texture/TopMenu/Shop_Up.PNG");
    topMenuBtnShop_Focus_Texture.loadFromFile("../Texture/TopMenu/Shop_Focus.PNG");
    TopMenu topMenuBtnShop(topMenuBtnShop_Up_Texture, sf::Vector2f(214 + (190 - 36) * 3, 2.5));

    // top menu button right
    sf::Texture topMenuBtnExit_Up_Texture;
    sf::Texture topMenuBtnExit_Down_Texture;
    topMenuBtnExit_Up_Texture.loadFromFile("../Texture/TopMenu/Exit_Up.PNG");
    topMenuBtnExit_Down_Texture.loadFromFile("../Texture/TopMenu/Exit_Down.PNG");
    TopMenu topMenuBtnExit(topMenuBtnExit_Down_Texture, sf::Vector2f(WIDTH - 100 + 6, 0));

    sf::Texture topMenuBtnOption_Up_Texture;
    sf::Texture topMenuBtnOption_Down_Texture;
    topMenuBtnOption_Up_Texture.loadFromFile("../Texture/TopMenu/Option_Up.PNG");
    topMenuBtnOption_Down_Texture.loadFromFile("../Texture/TopMenu/Option_Down.PNG");
    TopMenu topMenuBtnOption(topMenuBtnOption_Down_Texture, sf::Vector2f(WIDTH - 100 - 56, 0));

    sf::Texture topMenuBtnBack_Up_Texture;
    sf::Texture topMenuBtnBack_Down_Texture;
    topMenuBtnBack_Up_Texture.loadFromFile("../Texture/TopMenu/Back_Up.PNG");
    topMenuBtnBack_Down_Texture.loadFromFile("../Texture/TopMenu/Back_Down.PNG");
    TopMenu topMenuBtnBack(topMenuBtnBack_Down_Texture, sf::Vector2f(WIDTH - 100 - 56 * 2 - 6, 0));

    // character mainmenu display
    sf::Texture playerMainMenuBL_Texture;
    sf::Texture playerMainMenuGR_Texture;
    playerMainMenuBL_Texture.loadFromFile("../Texture/Character/Alexandrina_BL.png");
    playerMainMenuGR_Texture.loadFromFile("../Texture/Character/Alexandrina_GR.PNG");
    CharacterLobbyDisplay playerMainMenu(playerMainMenuBL_Texture, sf::Vector2f(WIDTH / 2, (HEIGHT / 2) + 25));

    // character title
    sf::Texture playerTitleBG_Texture;
    playerTitleBG_Texture.loadFromFile("../Texture/Character/character_title.PNG");
    CharacterTitleBG playerTitle(playerTitleBG_Texture, sf::Vector2f(WIDTH / 2, 47 + 30));

    // account display name
    TextManager accDisplayName(mainFont, "CKVN", 16, sf::Color::White, sf::Vector2f((WIDTH / 2) - 16, 62 + 6));

    // teams select
    sf::Texture BLTeam_Texture;
    sf::Texture BLTeam_Focus_Texture;
    sf::Texture BLTeam_Select_Texture;
    sf::Texture GRTeam_Texture;
    sf::Texture GRTeam_Focus_Texture;
    sf::Texture GRTeam_Select_Texture;
    BLTeam_Texture.loadFromFile("../Texture/bt_bl.PNG");
    BLTeam_Focus_Texture.loadFromFile("../Texture/bt_bl_focus.PNG");
    BLTeam_Select_Texture.loadFromFile("../Texture/bt_bl_select.PNG");
    GRTeam_Texture.loadFromFile("../Texture/bt_gr.PNG");
    GRTeam_Focus_Texture.loadFromFile("../Texture/bt_gr_focus.PNG");
    GRTeam_Select_Texture.loadFromFile("../Texture/bt_gr_select.PNG");
    TeamLobbyDisplaySelect BLTeam(BLTeam_Select_Texture, sf::Vector2f(935 + 45, 168 + 25));
    TeamLobbyDisplaySelect GRTeam(GRTeam_Texture, sf::Vector2f(935 + 85, 223 + 30));

    // button game start
    sf::Texture rightDownBtnPlay_Up_Texture;
    sf::Texture rightDownBtnPlay_Focus_Texture;
    rightDownBtnPlay_Up_Texture.loadFromFile("../Texture/GameStart_Up.PNG");
    rightDownBtnPlay_Focus_Texture.loadFromFile("../Texture/GameStart_Focus.PNG");
    RightPanel rightDownBtnPlay(rightDownBtnPlay_Up_Texture, sf::Vector2f(1415, 697));

    // button bag info
    sf::Texture rightDownBtnBagInfoMain_Texture;
    rightDownBtnBagInfoMain_Texture.loadFromFile("../Texture/Bag_Info_Main.PNG");
    RightPanel rightDownBtnBagInfoMain(rightDownBtnBagInfoMain_Texture, sf::Vector2f(1133, 658));

    // button match setting
    sf::Texture rightDownBtnMatchSetting_Up_Texture;
    sf::Texture rightDownBtnMatchSetting_Focus_Texture;
    rightDownBtnMatchSetting_Up_Texture.loadFromFile("../Texture/MatchSetting_Up.PNG");
    rightDownBtnMatchSetting_Focus_Texture.loadFromFile("../Texture/MatchSetting_Focus.PNG");
    RightPanel rightDownBtnMatchSetting(rightDownBtnMatchSetting_Up_Texture, sf::Vector2f(1134, 697));

    // map type bg
    sf::Texture rightDownBtnMapTypeBG_Texture;
    rightDownBtnMapTypeBG_Texture.loadFromFile("../Texture/MapTypeBG.PNG");
    RightPanel rightDownBtnMapTypeBG(rightDownBtnMapTypeBG_Texture, sf::Vector2f(1133, 747));

    // button myprofile
    sf::Texture footerBtnMyProfile_Up_Texture;
    sf::Texture footerBtnMyProfile_Focus_Texture;
    footerBtnMyProfile_Up_Texture.loadFromFile("../Texture/shortcut_Up.PNG");
    footerBtnMyProfile_Focus_Texture.loadFromFile("../Texture/shortcut_Focus.PNG");
    FooterMenu footerBtnMyProfile(footerBtnMyProfile_Up_Texture, sf::Vector2f(1133, 871));
    FooterMenu footerBtnMyClan(footerBtnMyProfile_Up_Texture, sf::Vector2f(1360, 871));

    // mode bg
    sf::Texture rightTopModeBG_Texture;
    rightTopModeBG_Texture.loadFromFile("../Texture/MatchInfo/Mode_BG2.PNG");
    RightPanel rightTopModeBG(rightTopModeBG_Texture, sf::Vector2f(1133, 100));

    // mode arrow btn
    sf::Texture rightTopBtnModeArrow_Texture;
    sf::Texture rightTopBtnModeArrow_Focus_Texture;
    rightTopBtnModeArrow_Texture.loadFromFile("../Texture/MatchInfo/Arrow.PNG");
    rightTopBtnModeArrow_Focus_Texture.loadFromFile("../Texture/MatchInfo/Arrow_Focus.PNG");
    RightPanel rightTopBtnModeArrow(rightTopBtnModeArrow_Texture, sf::Vector2f(1133, HEIGHT / 4));

    // banner 
    sf::Texture rightTopBanner_Texture;
    rightTopBanner_Texture.loadFromFile("../Texture/MatchInfo/banner0.PNG");
    RightPanel rightTopBanner(rightTopBanner_Texture, sf::Vector2f(1133, (HEIGHT / 2) + 42));

    // icon 
    sf::Texture rightTopIconRank_Texture;
    sf::Texture rightTopIconRecord_Texture;
    sf::Texture rightTopIconReward_Texture;
    sf::Texture rightTopIconMission_Texture;
    sf::Texture rightTopIconMedal_Texture;
    sf::Texture rightTopIconBG_Up_Texture;
    sf::Texture rightTopIconBG_Focus_Texture;
    rightTopIconRank_Texture.loadFromFile("../Texture/Icon/RankMatchIcon_Rank.PNG");
    rightTopIconRecord_Texture.loadFromFile("../Texture/Icon/RankMatchIcon_Record.PNG");
    rightTopIconReward_Texture.loadFromFile("../Texture/Icon/RankMatchIcon_Reward.PNG");
    rightTopIconMission_Texture.loadFromFile("../Texture/Icon/RankMatchIcon_Mission.PNG");
    rightTopIconMedal_Texture.loadFromFile("../Texture/Icon/RankMatchIcon_Medal.PNG");
    rightTopIconBG_Up_Texture.loadFromFile("../Texture/Icon/B_01_S_Up.PNG");
    rightTopIconBG_Focus_Texture.loadFromFile("../Texture/Icon/B_01_S_Focus.PNG");
    RightPanel rightTopIconRank(rightTopIconRank_Texture, sf::Vector2f(1133, (HEIGHT / 2) + 4));
    RightPanel rightTopIconRecord(rightTopIconRecord_Texture, sf::Vector2f(1133 + 47, (HEIGHT / 2) + 4));
    RightPanel rightTopIconReward(rightTopIconReward_Texture, sf::Vector2f(1133 + 46 * 2, (HEIGHT / 2) + 4));
    RightPanel rightTopIconMission(rightTopIconMission_Texture, sf::Vector2f(1133 + 45 * 3, (HEIGHT / 2) + 4));
    RightPanel rightTopIconMedal(rightTopIconMedal_Texture, sf::Vector2f(1133 + 45 * 4, (HEIGHT / 2) + 4));
    RightPanel rightTopIconBG_Rank(rightTopIconBG_Up_Texture, sf::Vector2f(1130, (HEIGHT / 2) + 2));
    RightPanel rightTopIconBG_Record(rightTopIconBG_Up_Texture, sf::Vector2f(1130+45, (HEIGHT / 2) + 2));
    RightPanel rightTopIconBG_Reward(rightTopIconBG_Up_Texture, sf::Vector2f(1130 + 45 * 2, (HEIGHT / 2) + 2));
    RightPanel rightTopIconBG_Mission(rightTopIconBG_Up_Texture, sf::Vector2f(1130 + 45 * 3, (HEIGHT / 2)+2));
    RightPanel rightTopIconBG_Medal(rightTopIconBG_Up_Texture, sf::Vector2f(1130 + 45 * 4, (HEIGHT / 2) + 2));

    // Event Page BG
    sf::Texture leftTopEventPageBG_Texture;
    leftTopEventPageBG_Texture.loadFromFile("../Texture/EventPage.PNG");
    LeftPanel leftTopEventPageBG(leftTopEventPageBG_Texture, sf::Vector2f(25, 128));

    // Slide BG
    sf::Texture leftSlideBG_Texture;
    leftSlideBG_Texture.loadFromFile("../Texture/SlideBG.PNG");
    LeftPanel leftSlideBG(leftSlideBG_Texture, sf::Vector2f(200, (HEIGHT / 6)-34));

    // Slide Icon
    sf::Texture leftSlideIcon_Texture;
    leftSlideIcon_Texture.loadFromFile("../Texture/SlideL_Up.PNG");
    LeftPanel leftSlideIcon(leftSlideIcon_Texture, sf::Vector2f(350 + 26, (HEIGHT / 2) - 48));

    // Image Cash BG
    sf::Texture leftTopImageCashBG_Texture;
    leftTopImageCashBG_Texture.loadFromFile("../Texture/ImgCashBG.PNG");
    LeftPanel leftTopImageCashBG(leftTopImageCashBG_Texture, sf::Vector2f(25, 64));

    // Page type btn
    sf::Texture leftTopPageTypeLBtn_Up_Texture;
    sf::Texture leftTopPageTypeLBtn_Select_Texture;
    sf::Texture leftTopPageTypeRBtn_Up_Texture;
    sf::Texture leftTopPageTypeRBtn_Select_Texture;
    leftTopPageTypeLBtn_Up_Texture.loadFromFile("../Texture/PageTypeL_Up.PNG");
    leftTopPageTypeLBtn_Select_Texture.loadFromFile("../Texture/PageTypeL_Select.PNG");
    leftTopPageTypeRBtn_Up_Texture.loadFromFile("../Texture/PageTypeR_Up.PNG");
    leftTopPageTypeRBtn_Select_Texture.loadFromFile("../Texture/PageTypeR_Select.PNG");
    LeftPanel leftTopPageTypeLBtn(leftTopPageTypeLBtn_Select_Texture, sf::Vector2f(25, 94));
    LeftPanel leftTopPageTypeRBtn(leftTopPageTypeRBtn_Up_Texture, sf::Vector2f(25 + 238, 94));

    // footer bg
    sf::Texture footerBG_Texture;
    footerBG_Texture.loadFromFile("../Texture/Bottom_BG.PNG");
    FooterMenu footerBG(footerBG_Texture, sf::Vector2f(0, HEIGHT-29));

    // footer map setting bg
    sf::Texture footerMapSetting_Texture;
    footerMapSetting_Texture.loadFromFile("../Texture/Buddy/BUDDY_BG.PNG");
    FooterMenu footerMapSetting(footerMapSetting_Texture, sf::Vector2f(25, HEIGHT - 31));

    // party btn
    sf::Texture leftPartyBtn_Texture;
    leftPartyBtn_Texture.loadFromFile("../Texture/PartyUI/B_02_Down.PNG");
    LeftPanel leftPartyFindBtn(leftPartyBtn_Texture, sf::Vector2f(354 - 102*2 + 23, HEIGHT - 180));
    LeftPanel leftPartyInviteBtn(leftPartyBtn_Texture, sf::Vector2f(354-102+25, HEIGHT - 180));

    // party invite member btn
    sf::Texture leftPartyLockBtn_Texture;
    leftPartyLockBtn_Texture.loadFromFile("../Texture/PartyUI/PartyMemberLocked.PNG");
    LeftPanel leftPartyLockBtn1(leftPartyLockBtn_Texture, sf::Vector2f(25, HEIGHT - 140));
    LeftPanel leftPartyLockBtn2(leftPartyLockBtn_Texture, sf::Vector2f(25 + 57 + 4, HEIGHT - 140));
    LeftPanel leftPartyLockBtn3(leftPartyLockBtn_Texture, sf::Vector2f(25+57*2 + 8, HEIGHT - 140));
    LeftPanel leftPartyLockBtn4(leftPartyLockBtn_Texture, sf::Vector2f(25+57*3 + 12, HEIGHT - 140));

    // party member avatar
    sf::Texture leftPartyMember_Texture;
    leftPartyMember_Texture.loadFromFile("../Texture/PartyUI/PartyMemberMe.PNG");
    LeftPanel leftPartyMember(leftPartyMember_Texture, sf::Vector2f(354 - 35*2, HEIGHT - 140));

    // party exit btn
    sf::Texture leftPartyExitBtn_Texture;
    leftPartyExitBtn_Texture.loadFromFile("../Texture/PartyUI/PartyExit_Dis.PNG");
    LeftPanel leftPartyExitBtn(leftPartyExitBtn_Texture, sf::Vector2f(354 - 10, HEIGHT - 140));

    // Get screen dimensions
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    int screenWidth = desktopMode.width;
    int screenHeight = desktopMode.height;

    // Calculate the position to center the window
    int windowPosX = (screenWidth - WIDTH) / 2;
    int windowPosY = (screenHeight - HEIGHT) / 2;

    // Set the window position
    window.setPosition(sf::Vector2i(windowPosX, windowPosY));

    while (window.isOpen())
    {
        // Delta time
        float deltaTime = deltaClock.restart().asSeconds();

        // Update logo animation
        logoSpr.update(deltaTime);

        // Handle event
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Handle window close
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Chỉ xử lý sự kiện chuột khi trạng thái là LOGIN, LOADING hoặc LOBBY
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (currentState == AppState::LOGIN) {
                    if (loginBtn.getGlobalBounds().contains(mousePosF)) {
                        currentState = AppState::LOBBY;
                        countdownTime = 2.8f; // Thay đổi thời gian đếm ngược theo yêu cầu của bạn
                    }
                    if (loginExitBtn.getGlobalBounds().contains(mousePosF))
                    {
                        window.close();
                    }
                    if (loginSavePasswordBtn.getGlobalBounds().contains(mousePosF))
                    {
                        // Chuyển trạng thái của nút
                        isSavePasswordEnabled = !isSavePasswordEnabled;

                        // Cập nhật texture dựa trên trạng thái
                        if (isSavePasswordEnabled)
                        {
                            loginSavePasswordBtn.setTexture(loginSavePasswordBtn_On_Texture);
                        }
                        else
                        {
                            loginSavePasswordBtn.setTexture(loginSavePasswordBtn_Off_Texture);
                        }
                    }
                    // Play button
                    if (topMenuBtnPlay.getGlobalBounds().contains(mousePosF)) {
                        playBtnClicked = true;
                        bagBtnClicked = false;
                        gachaBtnClicked = false;
                        shopBtnClicked = false;
                    }
                    // Bag button
                    else if (topMenuBtnBag.getGlobalBounds().contains(mousePosF)) {
                        playBtnClicked = false;
                        bagBtnClicked = true;
                        gachaBtnClicked = false;
                        shopBtnClicked = false;
                    }
                    // Gacha button
                    else if (topMenuBtnGacha.getGlobalBounds().contains(mousePosF)) {
                        playBtnClicked = false;
                        bagBtnClicked = false;
                        gachaBtnClicked = true;
                        shopBtnClicked = false;
                    }
                    // Shop button
                    else if (topMenuBtnShop.getGlobalBounds().contains(mousePosF)) {
                        playBtnClicked = false;
                        bagBtnClicked = false;
                        gachaBtnClicked = false;
                        shopBtnClicked = true;
                    }
                }
                else if (currentState == AppState::LOADING) {
                    if (countdownTime <= 0) {
                        currentState = AppState::LOGIN;
                        actionExecuted = false;
                    }
                }
                else if (currentState == AppState::LOBBY) {
                    // Start game
                    if (rightDownBtnPlay.getGlobalBounds().contains(mousePosF)) {
                        startGame();
                    }
                    // Exit button
                    if (topMenuBtnExit.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        window.close();
                    }
                    // change state to login
                    if (topMenuBtnBack.getGlobalBounds().contains(mousePosF)) {
                        currentState = AppState::LOGIN;
                    }
                    // BL team
                    if (BLTeam.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        BLTeam.setTexture(BLTeam_Select_Texture);
                        if (BLTeam.getPosition().x != 935 + 45)
                        {
                            BLTeam.setPosision(sf::Vector2f(935 + 45, BLTeam.getPosition().y));
                        }
                        GRTeam.setTexture(GRTeam_Texture);
                        if (GRTeam.getPosition().x != 935 + 85)
                        {
                            GRTeam.setPosision(sf::Vector2f(935 + 85, GRTeam.getPosition().y));
                        }
                        playerMainMenu.setTexture(playerMainMenuBL_Texture);
                    }
                    // GR team
                    if (GRTeam.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        BLTeam.setTexture(BLTeam_Texture);
                        if (BLTeam.getPosition().x == 935 + 45)
                        {
                            BLTeam.setPosision(sf::Vector2f(935 + 45 + 36, BLTeam.getPosition().y));
                        }
                        GRTeam.setTexture(GRTeam_Select_Texture);
                        if (GRTeam.getPosition().x == 935 + 85)
                        {
                            GRTeam.setPosision(sf::Vector2f(935 + 85 - 36, GRTeam.getPosition().y));
                        }
                        playerMainMenu.setTexture(playerMainMenuGR_Texture);
                    }

                    // Change top menu button left
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if (currentState == AppState::LOGIN) {
                    if (loginBtn.getGlobalBounds().contains(mousePosF)) {
                        loginBtn.setTexture(loginBtn_Focus_Texture);
                    }
                    else {
                        loginBtn.setTexture(loginBtn_Up_Texture);
                    }
                }
                else if (currentState == AppState::LOBBY) {
                    // Cập nhật trạng thái của các nút
                    // Play button
                    if (!playBtnClicked && topMenuBtnPlay.getGlobalBounds().contains(mousePosF)) {
                        topMenuBtnPlay.setTexture(topMenuBtnPlay_Focus_Texture);
                    }
                    else if (!playBtnClicked) {
                        topMenuBtnPlay.setTexture(topMenuBtnPlay_Up_Texture);
                    }

                    // Bag button
                    if (!bagBtnClicked && topMenuBtnBag.getGlobalBounds().contains(mousePosF)) {
                        topMenuBtnBag.setTexture(topMenuBtnBag_Focus_Texture);
                    }
                    else if (!bagBtnClicked) {
                        topMenuBtnBag.setTexture(topMenuBtnBag_Up_Texture);
                    }

                    // Gacha button
                    if (!gachaBtnClicked && topMenuBtnGacha.getGlobalBounds().contains(mousePosF)) {
                        topMenuBtnGacha.setTexture(topMenuBtnGacha_Focus_Texture);
                    }
                    else if (!gachaBtnClicked) {
                        topMenuBtnGacha.setTexture(topMenuBtnGacha_Up_Texture);
                    }

                    // Shop button
                    if (!shopBtnClicked && topMenuBtnShop.getGlobalBounds().contains(mousePosF)) {
                        topMenuBtnShop.setTexture(topMenuBtnShop_Focus_Texture);
                    }
                    else if (!shopBtnClicked) {
                        topMenuBtnShop.setTexture(topMenuBtnShop_Up_Texture);
                    }

                    // Play btn
                    if (rightDownBtnPlay.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        rightDownBtnPlay.setTexture(rightDownBtnPlay_Focus_Texture);
                    }
                    else
                    {
                        rightDownBtnPlay.setTexture(rightDownBtnPlay_Up_Texture);
                    }
                    // Match setting btn
                    if (rightDownBtnMatchSetting.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        rightDownBtnMatchSetting.setTexture(rightDownBtnMatchSetting_Focus_Texture);
                    }
                    else
                    {
                        rightDownBtnMatchSetting.setTexture(rightDownBtnMatchSetting_Up_Texture);
                    }
                    // Mode arrow btn
                    if (rightTopBtnModeArrow.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        rightTopBtnModeArrow.setTexture(rightTopBtnModeArrow_Focus_Texture);
                    }
                    else
                    {
                        rightTopBtnModeArrow.setTexture(rightTopBtnModeArrow_Texture);
                    }
                    // Back btn
                    if (topMenuBtnBack.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        topMenuBtnBack.setTexture(topMenuBtnBack_Up_Texture);
                    }
                    else
                    {
                        topMenuBtnBack.setTexture(topMenuBtnBack_Down_Texture);
                    }
                    // Option btn
                    if (topMenuBtnOption.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        topMenuBtnOption.setTexture(topMenuBtnOption_Up_Texture);
                    }
                    else
                    {
                        topMenuBtnOption.setTexture(topMenuBtnOption_Down_Texture);
                    }
                    // Quit
                    if (topMenuBtnExit.getGlobalBounds().contains(sf::Vector2f(mousePos)))
                    {
                        topMenuBtnExit.setTexture(topMenuBtnExit_Up_Texture);
                    }
                    else
                    {
                        topMenuBtnExit.setTexture(topMenuBtnExit_Down_Texture);
                    }
                }
            }

        }

        window.clear();

        // Vẽ các đối tượng dựa trên trạng thái hiện tại
        if (currentState == AppState::LOADING) {
            // Vẽ loading screen
            loadingScreen.draw(window);
            loadingScreenText.draw(window);
            if (countdownTime > 0) {
                countdownTime -= deltaTime;
            }

            if (countdownTime <= 0) {
                currentState = AppState::LOGIN;
            }
        }
        else if (currentState == AppState::LOGIN) {
            // Vẽ login screen
            loginBG.draw(window);
            loginBoxBG.draw(window);
            loginBtn.draw(window);
            accLogginName.draw(window);
            accLogginPass.draw(window);
            loginSavePasswordBtn.draw(window);
            loginCreateAccBtn.draw(window);
            loginFindPassBtn.draw(window);
            loginExitBtn.draw(window);
            //loginInputName.draw(window);
            //loginInputPassword.draw(window);
        }
        else if (currentState == AppState::LOBBY) {
            // Vẽ main menu
            // lobby bg
            mainMenuBG.draw(window);
            topMenuBg.draw(window);
            // logo
            logoSpr.draw(window);
            // top menu
            topMenuBtnPlay.draw(window);
            topMenuBtnBag.draw(window);
            topMenuBtnGacha.draw(window);
            topMenuBtnShop.draw(window);
            topMenuBtnExit.draw(window);
            topMenuBtnOption.draw(window);
            topMenuBtnBack.draw(window);
            playerMainMenu.draw(window);
            playerTitle.draw(window);
            accDisplayName.draw(window);
            BLTeam.draw(window);
            GRTeam.draw(window);
            // RIGHT MENU
            // right top
            rightTopModeBG.draw(window);
            rightTopBtnModeArrow.draw(window);
            rightTopBanner.draw(window);
            rightTopIconBG_Rank.draw(window);
            rightTopIconBG_Record.draw(window);
            rightTopIconBG_Reward.draw(window);
            rightTopIconBG_Mission.draw(window);
            rightTopIconBG_Medal.draw(window);
            rightTopIconRank.draw(window);
            rightTopIconRecord.draw(window);
            rightTopIconReward.draw(window);
            rightTopIconMission.draw(window);
            rightTopIconMedal.draw(window);
            // right down
            rightDownBtnBagInfoMain.draw(window);
            rightDownBtnMatchSetting.draw(window);
            rightDownBtnMapTypeBG.draw(window);
            rightDownBtnPlay.draw(window);
            // left top
            leftTopImageCashBG.draw(window);
            leftTopPageTypeLBtn.draw(window);
            leftTopPageTypeRBtn.draw(window);
            leftTopEventPageBG.draw(window);
            leftSlideBG.draw(window);
            leftSlideIcon.draw(window);
            // left down
            leftPartyFindBtn.draw(window);
            leftPartyInviteBtn.draw(window);
            leftPartyLockBtn1.draw(window);
            leftPartyLockBtn2.draw(window);
            leftPartyLockBtn3.draw(window);
            leftPartyLockBtn4.draw(window);
            leftPartyMember.draw(window);
            leftPartyExitBtn.draw(window);
            // footer menu
            footerBG.draw(window);
            footerMapSetting.draw(window);
            footerBtnMyProfile.draw(window);
            footerBtnMyClan.draw(window);
        }

        window.display();
    }

    return 0;
}
