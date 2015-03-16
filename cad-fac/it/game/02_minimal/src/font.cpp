#include "font.hpp"

const char NULL_STR = '\0';

FontTable::~FontTable( void ) {
    SDL_DestroyTexture( ft->font );
    delete[] ft->tex_name;
    delete[] ft->table;
    delete ft;
}

int FontTable::load( SDL_Renderer * r, const char * font ) {
    unsigned int text_size = 0, abc_size = 0;
    SDL_Texture *tex = nullptr;
    wint_t current = 0;
    size_t load = 1;
    int id = 0;
    FILE * f;

    render = r;
    ft = new font_table_t;
    f = fopen( font, "rb" );
    if ( f == nullptr ) {
        return ( last_error = A_ERROR_OPEN_FILE );
    }
    fread( &( text_size ), sizeof(int), 1, f );
    fread( &( abc_size ), sizeof(int), 1, f );
    ft->tex_name = new char [text_size];
    ft->table = new int [abc_size];
    fread( ft->tex_name, text_size, 1, f );
    fread( &( ft->t_width ), sizeof(int), 1, f );
    fread( &( ft->t_height ), sizeof(int), 1, f );
    tex = IMG_LoadTexture( render, ft->tex_name );
    ft->font = tex;
    if ( tex == nullptr ) {
        fclose( f );
        return ( last_error = A_ERROR_LOAD_TEXTURE );
    }
    SDL_QueryTexture( tex, nullptr, nullptr, &( ft->f_width ), &( ft->f_height ) );
    fseek( f, sizeof(int) * 4 + text_size + 1, SEEK_SET );
    do {
        load = fread( &current, 2, 1, f );
        if ( current != L'\n' && current < 0xFFFF && load != 0 ) {
            ft->table[current] = id++;
        }
    } while ( load != 0 );
    fclose( f );
    return ( last_error = A_SUCCESS );
}

void FontTable::draw( int x, int y, const wchar_t * text ) {
    SDL_Rect wnd = { 0, 0, ft->t_width, ft->t_height };
    SDL_Rect pos = { 0, 0, ft->t_width, ft->t_height };
    int dy = 0, i = 0, id = 0, old_x = x - ft->t_width;
    wint_t current;

    pos.x = old_x; pos.y = y;
    while ( ( current = text[i++] ) != NULL_STR ) {
        switch ( current ) {
            case '\n':
                pos.y += ft->t_height;
                pos.x = old_x;
                continue;
            case ' ':
                pos.x += ft->t_width;
                continue;
            case '\t':
                pos.x += 4 * ft->t_width;
                continue;
            // to upper
            case 'a'...'z':
            case L'а'...L'я':
                current -= 0x20;
                break;
        }
        id = ft->table[current];
        while ( id * ft->t_width >= ft->f_width ) {
            id -= ft->f_width / ft->t_width;
            dy++;
        }
        wnd.x = id * ft->t_width; wnd.y = dy * ft->t_height;
        pos.x += ft->t_width;
        SDL_RenderCopy( render, ft->font, &wnd, &pos );
        dy = 0;
    }
}

void FontTable::reload( SDL_Renderer * r ) {
    SDL_DestroyTexture( ft->font );
    ft->font = IMG_LoadTexture( r, ft->tex_name );
    render = r;
}

void FontTable::set_coloru( Uint32 color ) {
    SDL_SetTextureColorMod( ft->font, color >> 16, ( color >> 8 ) & 0xFF, color & 0xFF );
}