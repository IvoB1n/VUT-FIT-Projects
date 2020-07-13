/*!
 * @file
 * @brief This file contains implementation of gpu
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */

#include <student/gpu.hpp>


/// \addtogroup gpu_init
/// @{

/**
 * @brief Constructor of GPU
 */
GPU::GPU(){
  /// \todo Zde můžete alokovat/inicializovat potřebné proměnné grafické karty
}

/**
 * @brief Destructor of GPU
 */
GPU::~GPU(){
  /// \todo Zde můžete dealokovat/deinicializovat grafickou kartu
}

/// @}

/** \addtogroup buffer_tasks 01. Implementace obslužných funkcí pro buffery
 * @{
 */

/**
 * @brief This function allocates buffer on GPU.
 *
 * @param size size in bytes of new buffer on GPU.
 *
 * @return unique identificator of the buffer
 */
BufferID GPU::createBuffer(uint64_t size) { 
  /// \todo Tato funkce by měla na grafické kartě vytvořit buffer dat.<br>
  /// Velikost bufferu je v parameteru size (v bajtech).<br>
  /// Funkce by měla vrátit unikátní identifikátor identifikátor bufferu.<br>
  /// Na grafické kartě by mělo být možné alkovat libovolné množství bufferů o libovolné velikosti.<br>
  Buffer buffer;
  buffer.data = malloc(size);
  buffer.id = buffers.size();

  GPU::buffers.push_back(buffer);
  return GPU::buffers[GPU::buffers.size()-1].id;
}

/**
 * @brief This function frees allocated buffer on GPU.
 *
 * @param buffer buffer identificator
 */
void GPU::deleteBuffer(BufferID buffer) {
  /// \todo Tato funkce uvolní buffer na grafické kartě.
  /// Buffer pro smazání je vybrán identifikátorem v parameteru "buffer".
  /// Po uvolnění bufferu je identifikátor volný a může být znovu použit při vytvoření nového bufferu.
  std::vector<Buffer>::iterator item;
  for (item = GPU::buffers.begin(); item != GPU::buffers.end(); item++) {
    if (item->id == buffer) {
      free(item->data);
      GPU::buffers.erase(item);
      return;
    }
  }
}

/**
 * @brief This function uploads data to selected buffer on the GPU
 *
 * @param buffer buffer identificator
 * @param offset specifies the offset into the buffer's data
 * @param size specifies the size of buffer that will be uploaded
 * @param data specifies a pointer to new data
 */
void GPU::setBufferData(BufferID buffer, uint64_t offset, uint64_t size, void const* data) {
  /// \todo Tato funkce nakopíruje data z cpu na "gpu".<br>
  /// Data by měla být nakopírována do bufferu vybraného parametrem "buffer".<br>
  /// Parametr size určuje, kolik dat (v bajtech) se překopíruje.<br>
  /// Parametr offset určuje místo v bufferu (posun v bajtech) kam se data nakopírují.<br>
  /// Parametr data obsahuje ukazatel na data na cpu pro kopírování.<br>
  std::vector<Buffer>::iterator item;
  for (item = GPU::buffers.begin(); item !=GPU::buffers.end(); item++) {
    if (item->id == buffer) {
      memcpy((uint8_t*)item->data + offset, data, size);
      return;
    }
  }
}

/**
 * @brief This function downloads data from GPU.
 *
 * @param buffer specfies buffer
 * @param offset specifies the offset into the buffer from which data will be returned, measured in bytes. 
 * @param size specifies data size that will be copied
 * @param data specifies a pointer to the location where buffer data is returned. 
 */
void GPU::getBufferData(BufferID buffer,
                        uint64_t offset,
                        uint64_t size,
                        void*    data)
{
  /// \todo Tato funkce vykopíruje data z "gpu" na cpu.
  /// Data by měla být vykopírována z bufferu vybraného parametrem "buffer".<br>
  /// Parametr size určuje kolik dat (v bajtech) se překopíruje.<br>
  /// Parametr offset určuje místo v bufferu (posun v bajtech) odkud se začne kopírovat.<br>
  /// Parametr data obsahuje ukazatel, kam se data nakopírují.<br>
  std::vector<Buffer>::iterator item;
  for (item = GPU::buffers.begin(); item != GPU::buffers.end(); item++) {
    if (item->id == buffer) {
      memcpy(data, (uint8_t*)item->data + offset, size);
      return;
    }
  }
}

/**
 * @brief This function tests if buffer exists
 *
 * @param buffer selected buffer id
 *
 * @return true if buffer points to existing buffer on the GPU.
 */
bool GPU::isBuffer(BufferID buffer) { 
  /// \todo Tato funkce by měla vrátit true pokud buffer je identifikátor existující bufferu.<br>
  /// Tato funkce by měla vrátit false, pokud buffer není identifikátor existujícího bufferu. (nebo bufferu, který byl smazán).<br>
  /// Pro emptyId vrací false.<br>
  if (GPU::buffers.size() == 0) {
    return false;
  } else {
    std::vector<Buffer>::iterator item;
    for (item = GPU::buffers.begin(); item != GPU:: buffers.end(); item++) {
      if (item->id == buffer) {
        return true;
      }
    }
  }
  return false; 
}

/// @}

/**
 * \addtogroup vertexpuller_tasks 02. Implementace obslužných funkcí pro vertex puller
 * @{
 */

/**
 * @brief This function creates new vertex puller settings on the GPU,
 *
 * @return unique vertex puller identificator
 */
ObjectID GPU::createVertexPuller() {
  /// \todo Tato funkce vytvoří novou práznou tabulku s nastavením pro vertex puller.<br>
  /// Funkce by měla vrátit identifikátor nové tabulky.
  /// Prázdná tabulka s nastavením neobsahuje indexování a všechny čtecí hlavy jsou vypnuté.
  //return emptyID;
  Vertex_puller_settings_table vp_set_table;
  vp_set_table.vp_table_id = GPU::vp_set_tables.size();

  GPU::vp_set_tables.push_back(vp_set_table);
  return GPU::vp_set_tables[GPU::vp_set_tables.size()-1].vp_table_id;
}

/**
 * @brief This function deletes vertex puller settings
 *
 * @param vao vertex puller identificator
 */
void GPU::deleteVertexPuller(VertexPullerID vao) {
  /// \todo Tato funkce by měla odstranit tabulku s nastavení pro vertex puller.<br>
  /// Parameter "vao" obsahuje identifikátor tabulky s nastavením.<br>
  /// Po uvolnění nastavení je identifiktátor volný a může být znovu použit.<br>
  std::vector<Vertex_puller_settings_table>::iterator item;
  for (item = GPU::vp_set_tables.begin(); item != GPU::vp_set_tables.end(); item++) {
    if (item->vp_table_id == vao) {
      GPU::vp_set_tables.erase(item);
      return;
    }
  }
}

/**
 * @brief This function sets one vertex puller reading head.
 *
 * @param vao identificator of vertex puller
 * @param head id of vertex puller head
 * @param type type of attribute
 * @param stride stride in bytes
 * @param offset offset in bytes
 * @param buffer id of buffer
 */
void GPU::setVertexPullerHead(VertexPullerID vao,uint32_t head,AttributeType type,uint64_t stride,uint64_t offset,BufferID buffer) {
  /// \todo Tato funkce nastaví jednu čtecí hlavu vertex pulleru.<br>
  /// Parametr "vao" vybírá tabulku s nastavením.<br>
  /// Parametr "head" vybírá čtecí hlavu vybraného vertex pulleru.<br>
  /// Parametr "type" nastaví typ atributu, který čtecí hlava čte. Tímto se vybere kolik dat v bajtech se přečte.<br>
  /// Parametr "stride" nastaví krok čtecí hlavy.<br>
  /// Parametr "offset" nastaví počáteční pozici čtecí hlavy.<br>
  /// Parametr "buffer" vybere buffer, ze kterého bude čtecí hlava číst.<br>
  std::vector<Vertex_puller_settings_table>::iterator item;
  for (item = GPU::vp_set_tables.begin(); item != GPU::vp_set_tables.end(); item++) {
    if (item->vp_table_id == vao) {
      item->vp_head[head].id = buffer;
      item->vp_head[head].offset = offset;
      item->vp_head[head].stride = stride;
      item->vp_head[head].attrib_type = type;
      return;
    }
  }
}

/**
 * @brief This function sets vertex puller indexing.
 *
 * @param vao vertex puller id
 * @param type type of index
 * @param buffer buffer with indices
 */
void GPU::setVertexPullerIndexing(VertexPullerID vao,IndexType type,BufferID buffer) {
  /// \todo Tato funkce nastaví indexování vertex pulleru.
  /// Parametr "vao" vybírá tabulku s nastavením.<br>
  /// Parametr "type" volí typ indexu, který je uložený v bufferu.<br>
  /// Parametr "buffer" volí buffer, ve kterém jsou uloženy indexy.<br>
  std::vector<Vertex_puller_settings_table>::iterator item;
  for (item = GPU::vp_set_tables.begin(); item != GPU::vp_set_tables.end(); item++) {
    if (item->vp_table_id == vao) {
      item->vp_index.id = buffer;
      item->vp_index.index_type = type;
      return;
    }
  }
}

/**
 * @brief This function enables vertex puller's head.
 *
 * @param vao vertex puller 
 * @param head head id
 */
void GPU::enableVertexPullerHead (VertexPullerID vao,uint32_t head) {
  /// \todo Tato funkce povolí čtecí hlavu daného vertex pulleru.<br>
  /// Pokud je čtecí hlava povolena, hodnoty z bufferu se budou kopírovat do atributu vrcholů vertex shaderu.<br>
  /// Parametr "vao" volí tabulku s nastavením vertex pulleru (vybírá vertex puller).<br>
  /// Parametr "head" volí čtecí hlavu.<br>
  std::vector<Vertex_puller_settings_table>::iterator item;
  for (item = GPU::vp_set_tables.begin(); item != GPU::vp_set_tables.end(); item++) {
    if (item->vp_table_id == vao) {
      item->vp_head[head].enabled = true;
      return;
    }
  }
}

/**
 * @brief This function disables vertex puller's head
 *
 * @param vao vertex puller id
 * @param head head id
 */
void GPU::disableVertexPullerHead(VertexPullerID vao,uint32_t head) {
  /// \todo Tato funkce zakáže čtecí hlavu daného vertex pulleru.<br>
  /// Pokud je čtecí hlava zakázána, hodnoty z bufferu se nebudou kopírovat do atributu vrcholu.<br>
  /// Parametry "vao" a "head" vybírají vertex puller a čtecí hlavu.<br>
  std::vector<Vertex_puller_settings_table>::iterator item;
  for (item = GPU::vp_set_tables.begin(); item != GPU::vp_set_tables.end(); item++) {
    if (item->vp_table_id == vao) {
      item->vp_head[head].enabled = false;
      return;
    }
  }
}

/**
 * @brief This function selects active vertex puller.
 *
 * @param vao id of vertex puller
 */
void GPU::bindVertexPuller(VertexPullerID vao) {
  /// \todo Tato funkce aktivuje nastavení vertex pulleru.<br>
  /// Pokud je daný vertex puller aktivován, atributy z bufferů jsou vybírány na základě jeho nastavení.<br>
  current_vp = vao;
}

/**
 * @brief This function deactivates vertex puller.
 */
void GPU::unbindVertexPuller() {
  /// \todo Tato funkce deaktivuje vertex puller.
  /// To většinou znamená, že se vybere neexistující "emptyID" vertex puller.
  current_vp = emptyID;
}

/**
 * @brief This function tests if vertex puller exists.
 *
 * @param vao vertex puller
 *
 * @return true, if vertex puller "vao" exists
 */
bool GPU::isVertexPuller(VertexPullerID vao) {
  /// \todo Tato funkce otestuje, zda daný vertex puller existuje.
  /// Pokud ano, funkce vrací true.
  if (GPU::vp_set_tables.size() == 0) {
    return false;
  } else {
    std::vector<Vertex_puller_settings_table>::iterator item;
    for (item = GPU::vp_set_tables.begin(); item != GPU:: vp_set_tables.end(); item++) {
      if (item->vp_table_id == vao) {
        return true;
      }
    }
  }
  return false; 
}

/// @}

/** \addtogroup program_tasks 03. Implementace obslužných funkcí pro shader programy
 * @{
 */

/**
 * @brief This function creates new shader program.
 *
 * @return shader program id
 */
ProgramID GPU::createProgram() {
  /// \todo Tato funkce by měla vytvořit nový shader program.<br>
  /// Funkce vrací unikátní identifikátor nového proramu.<br>
  /// Program je seznam nastavení, které obsahuje: ukazatel na vertex a fragment shader.<br>
  /// Dále obsahuje uniformní proměnné a typ výstupních vertex attributů z vertex shaderu, které jsou použity pro interpolaci do fragment atributů.<br>
  Shader_program shader_program;
  shader_program.sp_id = GPU::shader_programs.size();
  for (uint8_t i; i < maxAttributes; i++) {
    shader_program.attributes[i] = AttributeType::EMPTY;
  }

  GPU::shader_programs.push_back(shader_program);
  return GPU::shader_programs[GPU::shader_programs.size()-1].sp_id;
}

/**
 * @brief This function deletes shader program
 *
 * @param prg shader program id
 */
void GPU::deleteProgram(ProgramID prg) {
  /// \todo Tato funkce by měla smazat vybraný shader program.<br>
  /// Funkce smaže nastavení shader programu.<br>
  /// Identifikátor programu se stane volným a může být znovu využit.<br>
  std::vector<Shader_program>::iterator item;
  for (item = GPU::shader_programs.begin(); item != GPU::shader_programs.end(); item++) {
    if (item->sp_id == prg) {
      GPU::shader_programs.erase(item);
      return;
    }
  }
}

/**
 * @brief This function attaches vertex and frament shader to shader program.
 *
 * @param prg shader program
 * @param vs vertex shader 
 * @param fs fragment shader
 */
void GPU::attachShaders(ProgramID prg,VertexShader vs,FragmentShader fs) {
  /// \todo Tato funkce by měla připojít k vybranému shader programu vertex a fragment shader.
  std::vector<Shader_program>::iterator item;
  for (item = GPU::shader_programs.begin(); item != GPU::shader_programs.end(); item++) {
    if (item->sp_id == prg) {
      item->vertex_shader = vs;
      item->fragment_shader = fs;
      return;
    }
  }
}

/**
 * @brief This function selects which vertex attributes should be interpolated during rasterization into fragment attributes.
 *
 * @param prg shader program
 * @param attrib id of attribute
 * @param type type of attribute
 */
void GPU::setVS2FSType(ProgramID prg,uint32_t attrib,AttributeType type) {
  /// \todo tato funkce by měla zvolit typ vertex atributu, který je posílán z vertex shaderu do fragment shaderu.<br>
  /// V průběhu rasterizace vznikají fragment.<br>
  /// Fragment obsahují fragment atributy.<br>
  /// Tyto atributy obsahují interpolované hodnoty vertex atributů.<br>
  /// Tato funkce vybere jakého typu jsou tyto interpolované atributy.<br>
  /// Bez jakéhokoliv nastavení jsou atributy prázdne AttributeType::EMPTY<br>
  std::vector<Shader_program>::iterator item;
  for (item = GPU::shader_programs.begin(); item != GPU::shader_programs.end(); item++) {
    if (item->sp_id == prg) {
      item->attributes[attrib] = type;
      return;
    }
  }
}

/**
 * @brief This function actives selected shader program
 *
 * @param prg shader program id
 */
void GPU::useProgram(ProgramID prg) {
  /// \todo tato funkce by měla vybrat aktivní shader program.
  current_sp = prg;
}

/**
 * @brief This function tests if selected shader program exists.
 *
 * @param prg shader program
 *
 * @return true, if shader program "prg" exists.
 */
bool GPU::isProgram(ProgramID prg) {
  /// \todo tato funkce by měla zjistit, zda daný program existuje.<br>
  /// Funkce vráti true, pokud program existuje.<br>
   if (GPU::shader_programs.size() == 0) {
    return false;
  } else {
    std::vector<Shader_program>::iterator item;
    for (item = GPU::shader_programs.begin(); item != GPU:: shader_programs.end(); item++) {
      if (item->sp_id == prg) {
        return true;
      }
    }
  }
  return false; 
}

/**
 * @brief This function sets uniform value (1 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void GPU::programUniform1f(ProgramID prg,uint32_t uniformId,float const&d) {
  /// \todo tato funkce by měla nastavit uniformní proměnnou shader programu.<br>
  /// Parametr "prg" vybírá shader program.<br>
  /// Parametr "uniformId" vybírá uniformní proměnnou. Maximální počet uniformních proměnných je uložen v programné \link maxUniforms \endlink.<br>
  /// Parametr "d" obsahuje data (1 float).<br>
  std::vector<Shader_program>::iterator item;
  for (item = GPU::shader_programs.begin(); item != GPU::shader_programs.end(); item++) {
    if (item->sp_id == prg) {
      item->uniforms.uniform[uniformId].v1 = d;
      return;
    }
  }
}

/**
 * @brief This function sets uniform value (2 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void GPU::programUniform2f(ProgramID prg,uint32_t uniformId,glm::vec2 const&d) {
  /// \todo tato funkce dělá obdobnou věc jako funkce programUniform1f.<br>
  /// Místo 1 floatu nahrává 2 floaty.
  std::vector<Shader_program>::iterator item;
  for (item = GPU::shader_programs.begin(); item != GPU::shader_programs.end(); item++) {
    if (item->sp_id == prg) {
      item->uniforms.uniform[uniformId].v2 = d;
      return;
    }
  }
}

/**
 * @brief This function sets uniform value (3 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void GPU::programUniform3f(ProgramID prg,uint32_t uniformId,glm::vec3 const&d) {
  /// \todo tato funkce dělá obdobnou věc jako funkce programUniform1f.<br>
  /// Místo 1 floatu nahrává 3 floaty.
  std::vector<Shader_program>::iterator item;
  for (item = GPU::shader_programs.begin(); item != GPU::shader_programs.end(); item++) {
    if (item->sp_id == prg) {
      item->uniforms.uniform[uniformId].v3 = d;
      return;
    }
  }
}

/**
 * @brief This function sets uniform value (4 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void GPU::programUniform4f(ProgramID prg,uint32_t uniformId,glm::vec4 const&d) {
  /// \todo tato funkce dělá obdobnou věc jako funkce programUniform1f.<br>
  /// Místo 1 floatu nahrává 4 floaty.
  std::vector<Shader_program>::iterator item;
  for (item = GPU::shader_programs.begin(); item != GPU::shader_programs.end(); item++) {
    if (item->sp_id == prg) {
      item->uniforms.uniform[uniformId].v4 = d;
      return;
    }
  }
}

/**
 * @brief This function sets uniform value (4 float).
 *
 * @param prg shader program
 * @param uniformId id of uniform value (number of uniform values is stored in maxUniforms variable)
 * @param d value of uniform variable
 */
void GPU::programUniformMatrix4f(ProgramID prg,uint32_t uniformId,glm::mat4 const&d) {
  /// \todo tato funkce dělá obdobnou věc jako funkce programUniform1f.<br>
  /// Místo 1 floatu nahrává matici 4x4 (16 floatů).
  std::vector<Shader_program>::iterator item;
  for (item = GPU::shader_programs.begin(); item != GPU::shader_programs.end(); item++) {
    if (item->sp_id == prg) {
      item->uniforms.uniform[uniformId].m4 = d;
      return;
    }
  }
}

/// @}

/** \addtogroup framebuffer_tasks 04. Implementace obslužných funkcí pro framebuffer
 * @{
 */

/**
 * @brief This function creates framebuffer on GPU.
 *
 * @param width width of framebuffer
 * @param height height of framebuffer
 */
void GPU::createFramebuffer(uint32_t width,uint32_t height) {
  /// \todo Tato funkce by měla alokovat framebuffer od daném rozlišení.<br>
  /// Framebuffer se skládá z barevného a hloukového bufferu.<br>
  /// Buffery obsahují width x height pixelů.<br>
  /// Barevný pixel je složen z 4 x uint8_t hodnot - to reprezentuje RGBA barvu.<br>
  /// Hloubkový pixel obsahuje 1 x float - to reprezentuje hloubku.<br>
  /// Nultý pixel framebufferu je vlevo dole.<br>
  GPU::frame_buffer.color_buffer = (uint8_t*)malloc(width*height * 4*sizeof(uint8_t));
  GPU::frame_buffer.depth_buffer = (float*)malloc(width*height * sizeof(float));

  GPU::H = height;
  GPU::W = width;
}

/**
 * @brief This function deletes framebuffer.
 */
void GPU::deleteFramebuffer() {
  /// \todo tato funkce by měla dealokovat framebuffer.
  free(frame_buffer.color_buffer);
  free(frame_buffer.depth_buffer);

  GPU::H = 0;
  GPU::W = 0;
}

/**
 * @brief This function resizes framebuffer.
 *
 * @param width new width of framebuffer
 * @param height new heght of framebuffer
 */
void GPU::resizeFramebuffer(uint32_t width,uint32_t height) {
  /// \todo Tato funkce by měla změnit velikost framebuffer.
  //frame_buffer.resize(width*height);  // TODO: починить удаление
  frame_buffer.color_buffer = (uint8_t*)realloc(frame_buffer.color_buffer, width*height * 4*sizeof(uint8_t));
  frame_buffer.depth_buffer = (float*)realloc(frame_buffer.depth_buffer, width*height * sizeof(float));

  GPU::H = height;
  GPU::W = width;
}

/**
 * @brief This function returns pointer to color buffer.
 *
 * @return pointer to color buffer
 */
uint8_t* GPU::getFramebufferColor() {
  /// \todo Tato funkce by měla vrátit ukazatel na začátek barevného bufferu.<br>
  return frame_buffer.color_buffer;
}

/**
 * @brief This function returns pointer to depth buffer.
 *
 * @return pointer to dept buffer.
 */
float* GPU::getFramebufferDepth() {
  /// \todo tato funkce by mla vrátit ukazatel na začátek hloubkového bufferu.<br>
  return frame_buffer.depth_buffer;
}

/**
 * @brief This function returns width of framebuffer
 *
 * @return width of framebuffer
 */
uint32_t GPU::getFramebufferWidth() {
  /// \todo Tato funkce by měla vrátit šířku framebufferu.
  return GPU::W;
}

/**
 * @brief This function returns height of framebuffer.
 *
 * @return height of framebuffer
 */
uint32_t GPU::getFramebufferHeight() {
  /// \todo Tato funkce by měla vrátit výšku framebufferu.
  return GPU::H;
}

/// @}

/** \addtogroup draw_tasks 05. Implementace vykreslovacích funkcí
 * Bližší informace jsou uvedeny na hlavní stránce dokumentace.
 * @{
 */

/**
 * @brief This functino clears framebuffer.
 *
 * @param r red channel
 * @param g green channel
 * @param b blue channel
 * @param a alpha channel
 */
void GPU::clear(float r,float g,float b,float a) {
  /// \todo Tato funkce by měla vyčistit framebuffer.<br>
  /// Barevný buffer vyčistí na barvu podle parametrů r g b a (0 - nulová intenzita, 1 a větší - maximální intenzita).<br>
  /// (0,0,0) - černá barva, (1,1,1) - bílá barva.<br>
  /// Hloubkový buffer nastaví na takovou hodnotu, která umožní rasterizaci trojúhelníka, který leží v rámci pohledového tělesa.<br>
  /// Hloubka by měla být tedy větší než maximální hloubka v NDC (normalized device coordinates).<br>
  float red = 0, green = 0, blue = 0, alpha = 0;
  if (r > 1) {
    red = 1;
  }
  if (r < 0) {
    red = 0;
  }
  if (g > 1) {
    green = 1;
  }
  if (g < 0) {
    green = 0;
  }
  if (b > 1) {
    blue = 1;
  }
  if (b < 0) {
    blue = 0;
  }
  if (a > 1) {
    alpha = 1;
  }
  if (a < 0) {
    alpha = 0;
  }

  for (uint64_t i = 0; i < GPU::W; i++) {
    for (uint64_t j = 0; j < GPU::H; j++) {
      frame_buffer.color_buffer[(GPU::W * i + j)*4] = static_cast<uint8_t>(red*255);
      frame_buffer.color_buffer[((GPU::W * i + j)*4) + 1] = static_cast<uint8_t>(green*255);
      frame_buffer.color_buffer[((GPU::W * i + j)*4) + 2] = static_cast<uint8_t>(blue*255);
      frame_buffer.color_buffer[((GPU::W * i + j)*4) + 3] = static_cast<uint8_t>(alpha);

      frame_buffer.depth_buffer[GPU::W * i + j] = 1.1f;
    }
  }
}

void GPU::drawTriangles(uint32_t  nofVertices){
  /// \todo Tato funkce vykreslí trojúhelníky podle daného nastavení.<br>
  /// Vrcholy se budou vybírat podle nastavení z aktivního vertex pulleru (pomocí bindVertexPuller).<br>
  /// Vertex shader a fragment shader se zvolí podle aktivního shader programu (pomocí useProgram).<br>
  /// Parametr "nofVertices" obsahuje počet vrcholů, který by se měl vykreslit (3 pro jeden trojúhelník).<br>
  std::vector<Buffer>::iterator BuffItem_vertex;
  std::vector<Buffer>::iterator BuffItem_index;
  std::vector<OutVertex>out_vertexes;
  std::vector<std::vector<OutVertex>>to_rasterize_triangles;
  InVertex in_vertex;
  OutVertex out_vertex;

  std::vector<Vertex_puller_settings_table>::iterator VPitem;
  for (VPitem = vp_set_tables.begin(); VPitem != vp_set_tables.end(); VPitem++) {
    if (VPitem->vp_table_id == current_vp) {
       break;
    }
  }
  std::vector<Shader_program>::iterator SPitem;
  for (SPitem = shader_programs.begin(); SPitem != shader_programs.end(); SPitem++) {
    if (SPitem->sp_id == current_sp) {
      break;
    }
  }

  for (uint32_t vertex = 0; vertex < nofVertices; vertex++) {
    in_vertex.gl_VertexID = vertex;
    for (uint32_t atrib = 0; atrib < maxAttributes; atrib++) {
      for (BuffItem_index = buffers.begin(); BuffItem_index != buffers.end(); BuffItem_index++) {
        if (BuffItem_index->id == VPitem->vp_index.id) {
          if (VPitem->vp_index.index_type == IndexType::UINT8) {
            uint8_t *data = (uint8_t*)BuffItem_index->data;
            in_vertex.gl_VertexID = (uint32_t)(data[vertex]);
          } else if ( VPitem->vp_index.index_type == IndexType::UINT16) {
            uint16_t *data = (uint16_t*)BuffItem_index->data;
            in_vertex.gl_VertexID = (uint32_t)(data[vertex]);
          } else {
            uint32_t *data = (uint32_t*)BuffItem_index->data;
            in_vertex.gl_VertexID = (uint32_t)(data[vertex]);
          } 
        }
      }
      for (BuffItem_vertex = buffers.begin(); BuffItem_vertex != buffers.end(); BuffItem_vertex++) {
        if (BuffItem_vertex->id == VPitem->vp_head[atrib].id){
          if (VPitem->vp_head[atrib].attrib_type == AttributeType::FLOAT) {
            setVS2FSType(current_sp, atrib, AttributeType::FLOAT);
            getBufferData(BuffItem_vertex->id, 
                          VPitem->vp_head[atrib].stride * in_vertex.gl_VertexID + VPitem->vp_head[atrib].offset, 
                          sizeof(float),
                          &(in_vertex.attributes[atrib].v1));
          }
          else if (VPitem->vp_head[atrib].attrib_type == AttributeType::VEC2) {
            setVS2FSType(current_sp, atrib, AttributeType::VEC2);
            getBufferData(BuffItem_vertex->id, 
                          VPitem->vp_head[atrib].stride * in_vertex.gl_VertexID + VPitem->vp_head[atrib].offset, 
                          sizeof(glm::vec2),
                          &(in_vertex.attributes[atrib].v2));                 
          }
          else if (VPitem->vp_head[atrib].attrib_type == AttributeType::VEC3) {
            setVS2FSType(current_sp, atrib, AttributeType::VEC3);
            getBufferData(BuffItem_vertex->id, 
                          VPitem->vp_head[atrib].stride * in_vertex.gl_VertexID + VPitem->vp_head[atrib].offset, 
                          sizeof(glm::vec3),
                          &(in_vertex.attributes[atrib].v3));
          }
          else if (VPitem->vp_head[atrib].attrib_type == AttributeType::VEC4) {
            setVS2FSType(current_sp, atrib, AttributeType::VEC4);
            getBufferData(BuffItem_vertex->id, 
                          VPitem->vp_head[atrib].stride * in_vertex.gl_VertexID + VPitem->vp_head[atrib].offset, 
                          sizeof(glm::vec4),
                          &(in_vertex.attributes[atrib].v4));
          }
        }
      }
    }
    SPitem->vertex_shader(out_vertex, in_vertex, SPitem->uniforms);
    out_vertexes.push_back(out_vertex);
    if (vertex % 3 == 2 ) {
      to_rasterize_triangles = clip_space_to_screen_space(out_vertexes);
      uint8_t num_of_trians = to_rasterize_triangles.size();
      if (num_of_trians != 0) {
        for (uint8_t i = 0; i < num_of_trians; i++) {
          rasterization(to_rasterize_triangles[i]);
        }
      }
      out_vertexes.clear();
    }
  }
}

std::vector<std::vector<OutVertex>> GPU::clip_space_to_screen_space(std::vector<OutVertex>triangle) {
  uint8_t to_clip = 0;
  std::vector<OutVertex>::iterator triangle_item;
  std::vector<OutVertex>to_rasterize_triangle(3);
  std::vector<std::vector<OutVertex>>to_rasterize_triangle_list;

  for (triangle_item = triangle.begin(); triangle_item != triangle.end(); triangle_item++) {
    if(-(triangle_item->gl_Position.w) > triangle_item->gl_Position.z) {
      to_clip++;
    }
  }
  
  if (to_clip == 0) {
    to_rasterize_triangle = perspective_division(triangle);
    
    to_rasterize_triangle = viewpoint_transformation(to_rasterize_triangle);
    to_rasterize_triangle_list.push_back(to_rasterize_triangle);
  }
  else if (to_clip == 1) {
    std::vector<OutVertex> to_rasterize_triangle1(3);
    std::vector<OutVertex> to_rasterize_triangle2(3);

    if (-triangle[0].gl_Position.w > triangle[0].gl_Position.z) {
      to_rasterize_triangle[0] = triangle[0];
      to_rasterize_triangle[1] = triangle[1];
      to_rasterize_triangle[2] = triangle[2];
    }
    else if (-triangle[1].gl_Position.w > triangle[1].gl_Position.z) {
      to_rasterize_triangle[0] = triangle[1];
      to_rasterize_triangle[1] = triangle[2];
      to_rasterize_triangle[2] = triangle[0];
    }
    else if (-triangle[2].gl_Position.w > triangle[2].gl_Position.z) {
      to_rasterize_triangle[0] = triangle[2];
      to_rasterize_triangle[1] = triangle[0];
      to_rasterize_triangle[2] = triangle[1];
    }

    to_rasterize_triangle1[0] = incision(to_rasterize_triangle[2], to_rasterize_triangle[0]);
    to_rasterize_triangle1[1] = to_rasterize_triangle[1];
    to_rasterize_triangle1[2] = to_rasterize_triangle[2];

    to_rasterize_triangle2[0] = incision(to_rasterize_triangle[1], to_rasterize_triangle[0]);
    to_rasterize_triangle2[1] = to_rasterize_triangle[1];
    to_rasterize_triangle2[2] = incision(to_rasterize_triangle[2], to_rasterize_triangle[0]);
    
    to_rasterize_triangle1 = perspective_division(to_rasterize_triangle1);
    to_rasterize_triangle1 = viewpoint_transformation(to_rasterize_triangle1);
    to_rasterize_triangle_list.push_back(to_rasterize_triangle1);

    to_rasterize_triangle2 = perspective_division(to_rasterize_triangle2);
    to_rasterize_triangle2 = viewpoint_transformation(to_rasterize_triangle2);
    to_rasterize_triangle_list.push_back(to_rasterize_triangle2);
  }
  else if (to_clip == 2) {   
    if (-triangle[0].gl_Position.w <= triangle[0].gl_Position.z) {
      to_rasterize_triangle[0] = triangle[0];
      to_rasterize_triangle[1] = incision(triangle[1], triangle[0]);
      to_rasterize_triangle[2] = incision(triangle[2], triangle[0]);
    } else if (-triangle[1].gl_Position.w <= triangle[1].gl_Position.z) {
      to_rasterize_triangle[0] = incision(triangle[0], triangle[1]);
      to_rasterize_triangle[1] = triangle[1];
      to_rasterize_triangle[2] = incision(triangle[2], triangle[1]);
    } 
     else {
      to_rasterize_triangle[0] = incision(triangle[0], triangle[2]);
      to_rasterize_triangle[1] = incision(triangle[1], triangle[2]);
      to_rasterize_triangle[2] = triangle[2];
    }
    to_rasterize_triangle = perspective_division(to_rasterize_triangle);
    to_rasterize_triangle = viewpoint_transformation(to_rasterize_triangle);
    to_rasterize_triangle_list.push_back(to_rasterize_triangle);
  } 

  return to_rasterize_triangle_list;
}

OutVertex GPU::incision(OutVertex vertex1, OutVertex vertex2) {
  OutVertex vertex_out;
  
  std::vector<Shader_program>::iterator sp_item;
  for (sp_item = shader_programs.begin(); sp_item != shader_programs.end(); sp_item++){
    if (sp_item->sp_id == current_sp){
      break;
    }
  }

  float t = (-vertex1.gl_Position.w - vertex1.gl_Position.z)/
                  (vertex2.gl_Position.w - vertex1.gl_Position.w
                  +vertex2.gl_Position.z - vertex1.gl_Position.z);
    
  vertex_out.gl_Position = vertex1.gl_Position + t*(vertex2.gl_Position - vertex1.gl_Position);

  for (uint32_t n = 0; n < maxAttributes; n++){
    if (sp_item->attributes[n] == AttributeType::FLOAT) {
      vertex_out.attributes[n].v1 = vertex1.attributes[n].v1 + t*(vertex2.attributes[n].v1 - vertex1.attributes[n].v1);
    } else if (sp_item->attributes[n] == AttributeType::VEC2) {
      vertex_out.attributes[n].v2 = vertex1.attributes[n].v2 + t*(vertex2.attributes[n].v2 - vertex1.attributes[n].v2);
    } else if (sp_item->attributes[n] == AttributeType::VEC3) {
      vertex_out.attributes[n].v3 = vertex1.attributes[n].v3 + t*(vertex2.attributes[n].v3 - vertex1.attributes[n].v3);
    } else if (sp_item->attributes[n] == AttributeType::VEC4) {
      vertex_out.attributes[n].v4 = vertex1.attributes[n].v4 + t*(vertex2.attributes[n].v4 - vertex1.attributes[n].v4);
    }
  }
  return vertex_out;
}

std::vector<OutVertex> GPU::perspective_division(std::vector<OutVertex>triangle) {
  std::vector<OutVertex>processed_triangle;

  std::vector<OutVertex>::iterator triangle_item;
  for(triangle_item = triangle.begin(); triangle_item != triangle.end(); triangle_item++) {
    OutVertex out_vertex;

    out_vertex.gl_Position.x = triangle_item->gl_Position.x / triangle_item->gl_Position.w;
    out_vertex.gl_Position.y = triangle_item->gl_Position.y / triangle_item->gl_Position.w;
    out_vertex.gl_Position.z = triangle_item->gl_Position.z / triangle_item->gl_Position.w;
  
    processed_triangle.push_back(out_vertex);
  }
  return processed_triangle;
}

std::vector<OutVertex> GPU::viewpoint_transformation(std::vector<OutVertex>triangle) {
  std::vector<OutVertex>processed_triangle;

  std::vector<OutVertex>::iterator triangle_item;
  for(triangle_item = triangle.begin(); triangle_item != triangle.end(); triangle_item++) {
    OutVertex out_vertex;
    
    out_vertex.gl_Position.x = ((triangle_item->gl_Position.x+1.0f)/2)*(GPU::W);
    out_vertex.gl_Position.y = ((triangle_item->gl_Position.y+1.0f)/2)*(GPU::H);
  
    processed_triangle.push_back(out_vertex);
  }
  return processed_triangle;
}

void GPU::rasterization(std::vector<OutVertex>triangle) {
  OutVertex a = triangle[0];
  OutVertex b = triangle[1];
  OutVertex c = triangle[2];
  float Eab;
  float Ebc;
  float Eca;
  
  std::vector<Shader_program>::iterator sp_item;
  for (sp_item = shader_programs.begin(); sp_item != shader_programs.end(); sp_item++){
    if (sp_item->sp_id == current_sp){
      break;
    }
  }

  if (((b.gl_Position.x - a.gl_Position.x) * (c.gl_Position.y - a.gl_Position.y))-
      ((b.gl_Position.y - a.gl_Position.y) * (c.gl_Position.x - a.gl_Position.x)) > 0) {
    b = triangle[2];
    c = triangle[1];
  }

  for (uint32_t y = 0; y < GPU::H; y++) {
    for (uint32_t x = 0; x < GPU::W; x++) {
      Eab = (((x+0.5f)-a.gl_Position.x)*(b.gl_Position.y-a.gl_Position.y))
           -(((y+0.5f)-a.gl_Position.y)*(b.gl_Position.x-a.gl_Position.x));
      Ebc = (((x+0.5f)-b.gl_Position.x)*(c.gl_Position.y-b.gl_Position.y))
           -(((y+0.5f)-b.gl_Position.y)*(c.gl_Position.x-b.gl_Position.x));
      Eca = (((x+0.5f)-c.gl_Position.x)*(a.gl_Position.y-c.gl_Position.y))
           -(((y+0.5f)-c.gl_Position.y)*(a.gl_Position.x-c.gl_Position.x));

      if ((Eab >= 0 && Ebc >= 0 && Eca >= 0) || (Eab < 0 && Ebc < 0 && Eca < 0)) {
        InFragment in_fragment;
        OutFragment out_fragment;

        in_fragment.gl_FragCoord.x = x + 0.5f;
        in_fragment.gl_FragCoord.y = y + 0.5f;

        in_fragment = interpolation(in_fragment, triangle);
        sp_item->fragment_shader(out_fragment, in_fragment, sp_item->uniforms);

        for (uint8_t i = 0; i < 4; i++) {
          if (out_fragment.gl_FragColor[i] > 1) {
            out_fragment.gl_FragColor[i] = 1;
          } else if (out_fragment.gl_FragColor[i] < 0) {
            out_fragment.gl_FragColor[i] = 0;
          }
          if (i != 3) {
            out_fragment.gl_FragColor[i] = static_cast<uint8_t>(out_fragment.gl_FragColor[i] *255);
          }
        }

        if (in_fragment.gl_FragCoord.z < frame_buffer.depth_buffer[GPU::W*y + x]) {
          frame_buffer.color_buffer[((GPU::W*y + x)*4)] = out_fragment.gl_FragColor.r;
          frame_buffer.color_buffer[((GPU::W*y + x)*4) + 1] = out_fragment.gl_FragColor.g;
          frame_buffer.color_buffer[((GPU::W*y + x)*4) + 2] = out_fragment.gl_FragColor.b;
          frame_buffer.color_buffer[((GPU::W*y + x)*4) + 3] = out_fragment.gl_FragColor.a;
          frame_buffer.depth_buffer[GPU::W*y + x] = in_fragment.gl_FragCoord.z;
        }
      }
    }
  }
}

InFragment GPU::interpolation(InFragment fragment, std::vector<OutVertex>triangle) {
  // https://www.mathopenref.com/coordtrianglearea.html
  // https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage
  
  OutVertex a = triangle[0];
  OutVertex b = triangle[1];
  OutVertex c = triangle[2];

  std::vector<Shader_program>::iterator sp_item;
  for (sp_item = shader_programs.begin(); sp_item != shader_programs.end(); sp_item++){
    if (sp_item->sp_id == current_sp){
      break;
    }
  }

  float abc_area;
  float pbc_area;
  float pca_area;
  float pab_area;

  abc_area = abs((a.gl_Position.x*(b.gl_Position.y - c.gl_Position.y)
                 +b.gl_Position.x*(c.gl_Position.y - a.gl_Position.y)
                 +c.gl_Position.x*(a.gl_Position.y - b.gl_Position.y))/2);
  pbc_area = abs((fragment.gl_FragCoord.x*(b.gl_Position.y - c.gl_Position.y)
                 +b.gl_Position.x*(c.gl_Position.y - fragment.gl_FragCoord.y)
                 +c.gl_Position.x*(fragment.gl_FragCoord.y - b.gl_Position.y))/2);
  pca_area = abs((a.gl_Position.x*(fragment.gl_FragCoord.y - c.gl_Position.y)
                 +fragment.gl_FragCoord.x*(c.gl_Position.y - a.gl_Position.y)
                 +c.gl_Position.x*(a.gl_Position.y - fragment.gl_FragCoord.y))/2);

  float la = pbc_area/abc_area;
  float lb = pca_area/abc_area;
  float lc = 1.0f - la - lb;

  fragment.gl_FragCoord.z = ((la*a.gl_Position.z)/a.gl_Position.w
                            +(lb*b.gl_Position.z)/b.gl_Position.w
                            +(lc*c.gl_Position.z)/c.gl_Position.w)
                            /(la/a.gl_Position.w + lb/b.gl_Position.w + lc/c.gl_Position.w);

  for (uint32_t i = 0; i < maxAttributes; i++) {
    if (sp_item->attributes[i] == AttributeType::FLOAT) {
      fragment.attributes[i].v1 = ((la*a.attributes[i].v1)/a.gl_Position.w
                                  +(lb*b.attributes[i].v1)/b.gl_Position.w
                                  +(lc*c.attributes[i].v1)/c.gl_Position.w)
                                  /(la/a.gl_Position.w + lb/b.gl_Position.w + lc/c.gl_Position.w);
    } else if (sp_item->attributes[i] == AttributeType::VEC2) {
      fragment.attributes[i].v2 = ((la*a.attributes[i].v2)/a.gl_Position.w
                                  +(lb*b.attributes[i].v2)/b.gl_Position.w
                                  +(lc*c.attributes[i].v2)/c.gl_Position.w)
                                  /(la/a.gl_Position.w + lb/b.gl_Position.w + lc/c.gl_Position.w);
    } else if (sp_item->attributes[i] == AttributeType::VEC3) {
      fragment.attributes[i].v3 = ((la*a.attributes[i].v3)/a.gl_Position.w
                                  +(lb*b.attributes[i].v3)/b.gl_Position.w
                                  +(lc*c.attributes[i].v3)/c.gl_Position.w)
                                  /(la/a.gl_Position.w + lb/b.gl_Position.w + lc/c.gl_Position.w);
    } else if (sp_item->attributes[i] == AttributeType::VEC4) {
      fragment.attributes[i].v4 = ((la*a.attributes[i].v4)/a.gl_Position.w
                                  +(lb*b.attributes[i].v4)/b.gl_Position.w
                                  +(lc*c.attributes[i].v4)/c.gl_Position.w)
                                  /(la/a.gl_Position.w + lb/b.gl_Position.w + lc/c.gl_Position.w);
    }
  }
  return fragment;
}
// }
/// @}
