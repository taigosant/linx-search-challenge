#ifndef _INC_DEFINES_H
#define _INC_DEFINES_H

#define TERM_SIZE 100
#define DESC_SIZE 4096

#endif

#ifndef LIBSTRING_H
#define LIBSTRING_H

#include <iostream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <string.h>


#ifndef valid_ch
#define valid_ch(ch)  (isalnum(ch))
#define invalid_ch(ch) (!valid_ch(ch))
#endif


class StringFormatter {
public:
    void normalize(std::string& sentence) {
        char str[DESC_SIZE], str_aux[DESC_SIZE], str_aux2[DESC_SIZE];
        strcpy(str, sentence.c_str());
        convert_buffer_without_accents(str, &str[strlen(str)], str_aux);
        clean(str_aux, &str_aux[strlen(str_aux)], str_aux2, DESC_SIZE);
        token(str_aux2, &str_aux2[strlen(str_aux2)], str_aux);

        sentence = str_aux2;
    }
    int get_next_term(const std::string& str, std::string& term, int n, int begin) {
        int i=0, j = 0, count=0;
        size_t allocSize = std::max(static_cast<size_t>(DESC_SIZE), str.size());
        char str_ch[allocSize], aux[allocSize];

        i = begin;

        strcpy(str_ch, str.c_str());
        aux[0] = '\0';
        while(_invalid[str_ch[i]] && str_ch[i] != '\0'){
            i++;
        }

        while(1) {
            if( _invalid[str_ch[i]]|| str_ch[i] == '\0') {
                while( _invalid[str_ch[i]]) i++;
                aux[j] = ' ';
                j++; count++;
                if(count==n) break;
            }
            aux[j] = str_ch[i];
            j++; i++;
        }

        aux[j-1] = '\0';
        term = aux;

        return i;
    }

private:
    char  _is_num[256];
    char  _valid[256];
    char  _invalid[256];
    unsigned char  _convert_with_accs[256];
    unsigned char  _convert_without_accs[256];
    unsigned char _upper_case[256];

    void clean(char *buff, char *end, char *new_text, int size) {
        int cont_char = 0;

        while(!(isalnum(*buff)) && (buff != end)){
            buff++;
        }

        while(buff != end) {
            if((isalnum(*buff)) || (*buff == ' ') ) {
                *new_text = *buff;
                new_text++; buff++;
                cont_char++;

                if(cont_char == size -1){ break; }
            }
            else{
                if(*buff == '/') {
                    *new_text = '/';
                    new_text++;
                }

                buff++;
            }
        }
        *new_text = 0;
        new_text--;
        if(*new_text == ' '){
            *new_text = 0;
        }
    }
    void start_valid() {
        unsigned x;

        for(x = 0; x < 128 ; x++) {
            _is_num[x]=0;
            if(valid_ch(x)) {
                _valid[x] = 1;
                _invalid[x] = 0;
            }
            else {
                _valid[x] = 0;
                _invalid[x] = 1;
            }
        }
        for( x = 128; x < 256; x++) {
            _is_num[x]=0;
            _valid[x] = 0;
            _invalid[x] = 1;
        }
        _valid[0]=_invalid[0]=0;
        for(x = 48; x < 58; x++) {
            _is_num[x] = 1;
        }
        _valid[224] = 1;  _invalid[224] = 0;
        _valid[225] = 1;  _invalid[225] = 0;
        _valid[226] = 1;  _invalid[226] = 0;
        _valid[227] = 1;  _invalid[227] = 0;
        _valid[228] = 1;  _invalid[228] = 0;
        _valid[229] = 1;  _invalid[229] = 0;
        _valid[231] = 1;  _invalid[231] = 0;
        _valid[232] = 1;  _invalid[232] = 0;
        _valid[233] = 1;  _invalid[233] = 0;
        _valid[234] = 1;  _invalid[234] = 0;
        _valid[235] = 1;  _invalid[235] = 0;
        _valid[236] = 1;  _invalid[236] = 0;
        _valid[237] = 1;  _invalid[237] = 0;
        _valid[238] = 1;  _invalid[238] = 0;
        _valid[239] = 1;  _invalid[239] = 0;
        _valid[241] = 1;  _invalid[241] = 0;
        _valid[242] = 1;  _invalid[242] = 0;
        _valid[243] = 1;  _invalid[243] = 0;
        _valid[244] = 1;  _invalid[244] = 0;
        _valid[245] = 1;  _invalid[245] = 0;
        _valid[246] = 1;  _invalid[246] = 0;
        _valid[249] = 1;  _invalid[249] = 0;
        _valid[250] = 1;  _invalid[250] = 0;
        _valid[251] = 1;  _invalid[251] = 0;
        _valid[252] = 1;  _invalid[252] = 0;
        _valid[253] = 1;  _invalid[253] = 0;
        _valid[255] = 1;  _invalid[255] = 0;
        _valid['/'] = 1;  _invalid['/'] = 0;
        _valid['.'] = 1;  _invalid['.'] = 0;
    }
    void start_convert_without_accents() {
        unsigned x;

        start_valid();
        for(x = 1; x < 65 ; x++) {
            _convert_without_accs[x] = x;
        }
        for(x = 65; x < 91; x++) {
            _convert_without_accs[x] = x+32;
        }
        for(; x < 128; x++) {
            _convert_without_accs[x] = x;
        }
        _convert_without_accs[45] = 45;
        _convert_without_accs[128] = 99; // 0x80
        _convert_without_accs[129] = 0;
        _convert_without_accs[130] = 0;
        _convert_without_accs[131] = 0;
        _convert_without_accs[132] = 0;
        _convert_without_accs[133] = 32; //0x85
        _convert_without_accs[134] = 0;
        _convert_without_accs[135] = 32; // 87
        _convert_without_accs[136] = 0;
        _convert_without_accs[137] = 0;
        _convert_without_accs[138] = 0; // 0x8A
        _convert_without_accs[139] = 0;
        _convert_without_accs[140] = 0;
        _convert_without_accs[141] = 0;
        _convert_without_accs[142] = 0;
        _convert_without_accs[143] = 0; // 8F
        _convert_without_accs[144] = 0; // 90
        _convert_without_accs[145] = 32;
        _convert_without_accs[146] = 32;
        _convert_without_accs[147] = 32;
        _convert_without_accs[148] = 32;
        _convert_without_accs[149] = 32; // 95
        _convert_without_accs[150] = 32;
        _convert_without_accs[151] = 32;
        _convert_without_accs[152] = 32;
        _convert_without_accs[153] = 32;
        _convert_without_accs[154] = 32; // 9A
        _convert_without_accs[155] = 0;
        _convert_without_accs[156] = 0;
        _convert_without_accs[157] = 0;
        _convert_without_accs[158] = 0;
        _convert_without_accs[159] = 0;  // 9F
        _convert_without_accs[160] = 32; // A0
        _convert_without_accs[161] = 161;
        _convert_without_accs[162] = 162;
        _convert_without_accs[163] = 163;
        _convert_without_accs[164] = 164;
        _convert_without_accs[165] = 165; //A5
        _convert_without_accs[166] = 166;
        _convert_without_accs[167] = 167;
        _convert_without_accs[168] = 168;
        _convert_without_accs[169] = 169;
        _convert_without_accs[170] = 32; //AA
        _convert_without_accs[171] = 171;
        _convert_without_accs[172] = 172;
        _convert_without_accs[173] = 173;
        _convert_without_accs[174] = 174;
        _convert_without_accs[175] = 175; //AF
        _convert_without_accs[176] = 176; //B0
        _convert_without_accs[177] = 177;
        _convert_without_accs[178] = 178;
        _convert_without_accs[179] = 179;
        _convert_without_accs[180] = 180;
        _convert_without_accs[181] = 181; //B5
        _convert_without_accs[182] = 182;
        _convert_without_accs[183] = 183;
        _convert_without_accs[184] = 184;
        _convert_without_accs[185] = 185;
        _convert_without_accs[186] = 186; // BA
        _convert_without_accs[187] = 187;
        _convert_without_accs[188] = 188;
        _convert_without_accs[189] = 189;
        _convert_without_accs[190] = 190;
        _convert_without_accs[191] = 191; //BF
        _convert_without_accs[192] = 97;  // C0
        _convert_without_accs[193] = 97;
        _convert_without_accs[194] = 97;
        _convert_without_accs[195] = 97;
        _convert_without_accs[196] = 97;
        _convert_without_accs[197] = 97; // C5
        _convert_without_accs[198] = 198;
        _convert_without_accs[199] = 99;
        _convert_without_accs[200] = 101;
        _convert_without_accs[201] = 101;
        _convert_without_accs[202] = 101; // CA
        _convert_without_accs[203] = 101;
        _convert_without_accs[204] = 105;
        _convert_without_accs[205] = 105;
        _convert_without_accs[206] = 105;
        _convert_without_accs[207] = 105; // CF
        _convert_without_accs[208] = 208; // D0
        _convert_without_accs[209] = 110;
        _convert_without_accs[210] = 111;
        _convert_without_accs[211] = 111;
        _convert_without_accs[212] = 111;
        _convert_without_accs[213] = 111; // D5
        _convert_without_accs[214] = 111;
        _convert_without_accs[215] = 215;
        _convert_without_accs[216] = 216;
        _convert_without_accs[217] = 117;
        _convert_without_accs[218] = 117; // DA
        _convert_without_accs[219] = 117;
        _convert_without_accs[220] = 117;
        _convert_without_accs[221] = 121;
        _convert_without_accs[222] = 122;
        _convert_without_accs[223] = 223; //DF
        _convert_without_accs[224] = 97 ; // E0
        _convert_without_accs[225] = 97 ;
        _convert_without_accs[226] = 97 ;
        _convert_without_accs[227] = 97 ;
        _convert_without_accs[228] = 97 ;
        _convert_without_accs[229] = 97 ; // E5
        _convert_without_accs[230] = 230;
        _convert_without_accs[231] = 99 ;
        _convert_without_accs[232] = 101;
        _convert_without_accs[233] = 101;
        _convert_without_accs[234] = 101; // EA
        _convert_without_accs[235] = 101;
        _convert_without_accs[236] = 105;
        _convert_without_accs[237] = 105;
        _convert_without_accs[238] = 105;
        _convert_without_accs[239] = 105; // EF
        _convert_without_accs[240] = 240; // F0
        _convert_without_accs[241] = 110;
        _convert_without_accs[242] = 111;
        _convert_without_accs[243] = 111;
        _convert_without_accs[244] = 111;
        _convert_without_accs[245] = 111; // F5
        _convert_without_accs[246] = 111;
        _convert_without_accs[247] = 247;
        _convert_without_accs[248] = 248;
        _convert_without_accs[249] = 117;
        _convert_without_accs[250] = 117; // FA
        _convert_without_accs[251] = 117;
        _convert_without_accs[252] = 117;
        _convert_without_accs[253] = 121;
        _convert_without_accs[254] = 254;
        _convert_without_accs[255] = 121; // FF

    }
    void start_convert_with_accents() {
        unsigned x;

        start_valid();
        for(x = 1; x < 65 ; x++) {
            _convert_with_accs[x] = x;
        }
        for(x = 65; x < 91; x++) {
            _convert_with_accs[x] = x+32;
        }
        for(; x < 128; x++) {
            _convert_with_accs[x] = x;
        }
        _convert_with_accs[45] = 45;
        _convert_with_accs[128] = 231; // 0x80
        _convert_with_accs[129] = 0;
        _convert_with_accs[130] = 0;
        _convert_with_accs[131] = 0;
        _convert_with_accs[132] = 0;
        _convert_with_accs[133] = 133; //0x85
        _convert_with_accs[134] = 0;
        _convert_with_accs[135] = 135; // 87
        _convert_with_accs[136] = 0;
        _convert_with_accs[137] = 0;
        _convert_with_accs[138] = 0; // 0x8A
        _convert_with_accs[139] = 0;
        _convert_with_accs[140] = 0;
        _convert_with_accs[141] = 0;
        _convert_with_accs[142] = 0;
        _convert_with_accs[143] = 0; // 8F
        _convert_with_accs[144] = 0; // 90
        _convert_with_accs[145] = 145;
        _convert_with_accs[146] = 146;
        _convert_with_accs[147] = 147;
        _convert_with_accs[148] = 148;
        _convert_with_accs[149] = 149; //95
        _convert_with_accs[150] = 150;
        _convert_with_accs[151] = 151;
        _convert_with_accs[152] = 152;
        _convert_with_accs[153] = 153;
        _convert_with_accs[154] = 154; // 9A
        _convert_with_accs[155] = 0; // 9B
        _convert_with_accs[156] = 0;
        _convert_with_accs[157] = 0;
        _convert_with_accs[158] = 0;
        _convert_with_accs[159] = 0; // 9F
        _convert_with_accs[160] = 160; // A0
        _convert_with_accs[161] = 161;
        _convert_with_accs[162] = 162;
        _convert_with_accs[163] = 163;
        _convert_with_accs[164] = 164;
        _convert_with_accs[165] = 165; //A5
        _convert_with_accs[166] = 166;
        _convert_with_accs[167] = 167;
        _convert_with_accs[168] = 168;
        _convert_with_accs[169] = 169;
        _convert_with_accs[170] = 170; //AA
        _convert_with_accs[171] = 171;
        _convert_with_accs[172] = 172;
        _convert_with_accs[173] = 173;
        _convert_with_accs[174] = 174;
        _convert_with_accs[175] = 175; //AF
        _convert_with_accs[176] = 176; //B0
        _convert_with_accs[177] = 177;
        _convert_with_accs[178] = 178;
        _convert_with_accs[179] = 179;
        _convert_with_accs[180] = 180;
        _convert_with_accs[181] = 181; //B5
        _convert_with_accs[182] = 182;
        _convert_with_accs[183] = 183;
        _convert_with_accs[184] = 184;
        _convert_with_accs[185] = 185;
        _convert_with_accs[186] = 186; //BA
        _convert_with_accs[187] = 187;
        _convert_with_accs[188] = 188;
        _convert_with_accs[189] = 189;
        _convert_with_accs[190] = 190;
        _convert_with_accs[191] = 191; //BF
        _convert_with_accs[192] = 224; //C0
        _convert_with_accs[193] = 225;
        _convert_with_accs[194] = 226;
        _convert_with_accs[195] = 227;
        _convert_with_accs[196] = 228;
        _convert_with_accs[197] = 229; //C5
        _convert_with_accs[198] = 198;
        _convert_with_accs[199] = 231;
        _convert_with_accs[200] = 232;
        _convert_with_accs[201] = 233;
        _convert_with_accs[202] = 234; // CA
        _convert_with_accs[203] = 235;
        _convert_with_accs[204] = 236;
        _convert_with_accs[205] = 237;
        _convert_with_accs[206] = 238;
        _convert_with_accs[207] = 239; //CF
        _convert_with_accs[208] = 208; //D0
        _convert_with_accs[209] = 241;
        _convert_with_accs[210] = 242;
        _convert_with_accs[211] = 243;
        _convert_with_accs[212] = 244;
        _convert_with_accs[213] = 245; // D5
        _convert_with_accs[214] = 246;
        _convert_with_accs[215] = 215;
        _convert_with_accs[216] = 216;
        _convert_with_accs[217] = 249;
        _convert_with_accs[218] = 250; //DA
        _convert_with_accs[219] = 251;
        _convert_with_accs[220] = 252;
        _convert_with_accs[221] = 253; // 253
        _convert_with_accs[222] = 222;
        _convert_with_accs[223] = 223; // DF
        _convert_with_accs[224] = 224; //E0
        _convert_with_accs[225] = 225;
        _convert_with_accs[226] = 226;
        _convert_with_accs[227] = 227;
        _convert_with_accs[228] = 228;
        _convert_with_accs[229] = 229; //E5
        _convert_with_accs[230] = 230;
        _convert_with_accs[231] = 231;
        _convert_with_accs[232] = 232;
        _convert_with_accs[233] = 233;
        _convert_with_accs[234] = 234; //EA
        _convert_with_accs[235] = 235;
        _convert_with_accs[236] = 236;
        _convert_with_accs[237] = 237;
        _convert_with_accs[238] = 238;
        _convert_with_accs[239] = 239; //EF
        _convert_with_accs[240] = 240; //F0
        _convert_with_accs[241] = 241;
        _convert_with_accs[242] = 242;
        _convert_with_accs[243] = 243;
        _convert_with_accs[244] = 244;
        _convert_with_accs[245] = 245; //F5
        _convert_with_accs[246] = 246;
        _convert_with_accs[247] = 247;
        _convert_with_accs[248] = 248;
        _convert_with_accs[249] = 249;
        _convert_with_accs[250] = 250; //FA
        _convert_with_accs[251] = 251;
        _convert_with_accs[252] = 252;
        _convert_with_accs[253] = 253;
        _convert_with_accs[254] = 254;
        _convert_with_accs[255] = 255;

        for(x = 0; x < 97; x++) {
            _upper_case[x] = x;
        }
        for(x = 97; x < 123; x++) {
            _upper_case[x] = x-32;
        }
        for(x = 123; x < 224; x++) {
            _upper_case[x] = x;
        }
        for(x = 224; x < 253; x++) {
            _upper_case[x] = x-32;
        }
    }
    char convert_buffer_utf8(char ch) {
        switch( (int)ch ) {
            case -92:{ return 'a'; break; }
            case -93:{ return 'a'; break; }
            case -94:{ return 'a'; break; }
            case -95:{ return 'a'; break; }
            case -96:{ return 'a'; break; }
            case -124:{ return 'a'; break; }
            case -125:{ return 'a'; break; }
            case -126:{ return 'a'; break; }
            case -127:{ return 'a'; break; }
            case -128:{ return 'a'; break; }
            case -85:{ return 'e'; break; }
            case -86:{ return 'e'; break; }
            case -87:{ return 'e'; break; }
            case -88:{ return 'e'; break; }
            case -117:{ return 'e'; break; }
            case -118:{ return 'e'; break; }
            case -119:{ return 'e'; break; }
            case -120:{ return 'e'; break; }
            case -81:{ return 'i'; break; }
            case -82:{ return 'i'; break; }
            case -83:{ return 'i'; break; }
            case -84:{ return 'i'; break; }
            case -113:{ return 'i'; break; }
            case -114:{ return 'i'; break; }
            case -115:{ return 'i'; break; }
            case -116:{ return 'i'; break; }
            case -74:{ return 'o'; break; }
            case -75:{ return 'o'; break; }
            case -76:{ return 'o'; break; }
            case -77:{ return 'o'; break; }
            case -78:{ return 'o'; break; }
            case -106:{ return 'o'; break; }
            case -107:{ return 'o'; break; }
            case -108:{ return 'o'; break; }
            case -109:{ return 'o'; break; }
            case -110:{ return 'o'; break; }
            case -68:{ return 'u'; break; }
            case -69:{ return 'u'; break; }
            case -70:{ return 'u'; break; }
            case -71:{ return 'u'; break; }
            case -100:{ return 'u'; break; }
            case -101:{ return 'u'; break; }
            case -102:{ return 'u'; break; }
            case -103:{ return 'u'; break; }
            case -89:{ return 'c'; break; }
            case -121:{ return 'c'; break; }
            default: { return ch; }
        }
    }
    void convert_buffer_without_accents(char *ch, char *end, char *new_) {
        start_convert_without_accents();

        while(ch < end) {
            if(*ch < 0) {
                if(*ch == -61) {
                    ch++;
                    *new_ = convert_buffer_utf8(*ch);
                    new_++;
                }
            }
            else{
                *new_ = _convert_without_accs[*ch];
                new_++;
            }
            ch++;
        }
        *new_ = '\0';
    }
    int alpha_num_token(char *token , char *end) {
        int cont_alpha=0, cont_num = 0;
        while(token != end) {
            if(isalpha(*token)) { cont_alpha++; }
            else{
                if(isdigit(*token)) { cont_num++; }
            }

            if((cont_alpha > 0) && (cont_num > 0)) {
                return 1;
            }
            token++;
        }
        return 0;
    }
    void break_token(char *token , char *end, char *new_) {
        char c = *token;
        int alpha = 0;

        if(isalpha(c)) { alpha = 1; }

        while(token != end) {
            if(alpha == 1) {
                while((!(isdigit(*token))) && (token != end)) {
                    *new_ = *token; new_++; token++;
                }
            }
            else{
                while((!(isalpha(*token))) && (token != end)) {
                    *new_ = *token; new_++; token++;
                }
            }

            if(token != end) {
                *new_ = ' '; new_++;
            }

            alpha = 0;
            if(isalpha(*token)) { alpha = 1; }
        }
        *new_ = '\0';
    }
    void token( char *text, char *end, char *new_tokens) {
        char buffer[DESC_SIZE];
        char temp[DESC_SIZE];
        int i=0, control=0;

        new_tokens[0] = '\0';

        while(text != end) {
            i = 0;

            if(*text == 0) {
                break;
            }

            while((*text != ' ') && (text != end)) {
                buffer[i] = *text;
                text++; i++;
            }
            buffer[i] = '\0';

            if(alpha_num_token( buffer, &buffer[i])) {
                break_token(buffer, &buffer[i], temp);

                if(control) {
                    strcat(new_tokens, " ");
                }
                strcat(new_tokens, temp);
                control++;
            }

            if(text != end){  text++; }
        }
    }

public:
    StringFormatter() {
        start_valid();
        start_convert_with_accents();
        start_convert_without_accents();
    }

};

#endif
