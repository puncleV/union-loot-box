var int rx_lootbox_opened_times;

instance itmi_lootbox(c_item) {
    name = "???";
    mainflag = item_kat_none;
    flags = item_multi | item_mission;
    value = 100;
    visual = "ITMI_POCKET_BIG.3ds";
    scemename = "MAPSEALED";
    material = mat_leather;
    on_state = use_itmi_lootbox;
    description = name;
    text[4] = "???";
    text[5] = name_value;
    count[5] = value;
    inv_animate = 1;
};

func void use_itmi_lootbox() {
    punclev_open_loot_box();

    ai_printbonus("You've been blessed with new item!");
};

func void b_givetradeinv(var c_npc slf) {
    var c_npc trd_kardif;
    
    trd_kardif = hlp_getnpc(vlk_431_kardif);
    
    if(hlp_getinstanceid(slf) == hlp_getinstanceid(trd_kardif)) {
        ai_printbonus("What are those boxes???");
        npc_removeinvitems(slf, itmi_lootbox, npc_hasitems(slf, itmi_lootbox));
        createinvitems(slf, itmi_lootbox, 100);
    };
    
    b_givetradeinv_old(slf);
};
