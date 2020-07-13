/*!
 * @file
 * @brief This file contains class that represents graphic card.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */
#pragma once

#include <student/fwd.hpp>
//
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iterator>
/**
 * @brief This class represent software GPU
 */
class GPU{
  public:
    GPU();
    virtual ~GPU();

    //buffer object commands
    BufferID  createBuffer           (uint64_t size);
    void      deleteBuffer           (BufferID buffer);
    void      setBufferData          (BufferID buffer,uint64_t offset,uint64_t size,void const* data);
    void      getBufferData          (BufferID buffer,uint64_t offset,uint64_t size,void      * data);
    bool      isBuffer               (BufferID buffer);

    //vertex array object commands (vertex puller)
    ObjectID  createVertexPuller     ();
    void      deleteVertexPuller     (VertexPullerID vao);
    void      setVertexPullerHead    (VertexPullerID vao,uint32_t head,AttributeType type,uint64_t stride,uint64_t offset,BufferID buffer);
    void      setVertexPullerIndexing(VertexPullerID vao,IndexType type,BufferID buffer);
    void      enableVertexPullerHead (VertexPullerID vao,uint32_t head);
    void      disableVertexPullerHead(VertexPullerID vao,uint32_t head);
    void      bindVertexPuller       (VertexPullerID vao);
    void      unbindVertexPuller     ();
    bool      isVertexPuller         (VertexPullerID vao);

    //program object commands
    ProgramID createProgram          ();
    void      deleteProgram          (ProgramID prg);
    void      attachShaders          (ProgramID prg,VertexShader vs,FragmentShader fs);
    void      setVS2FSType           (ProgramID prg,uint32_t attrib,AttributeType type);
    void      useProgram             (ProgramID prg);
    bool      isProgram              (ProgramID prg);
    void      programUniform1f       (ProgramID prg,uint32_t uniformId,float     const&d);
    void      programUniform2f       (ProgramID prg,uint32_t uniformId,glm::vec2 const&d);
    void      programUniform3f       (ProgramID prg,uint32_t uniformId,glm::vec3 const&d);
    void      programUniform4f       (ProgramID prg,uint32_t uniformId,glm::vec4 const&d);
    void      programUniformMatrix4f (ProgramID prg,uint32_t uniformId,glm::mat4 const&d);

    //framebuffer functions
    void      createFramebuffer      (uint32_t width,uint32_t height);
    void      deleteFramebuffer      ();
    void      resizeFramebuffer      (uint32_t width,uint32_t height);
    uint8_t*  getFramebufferColor    ();
    float*    getFramebufferDepth    ();
    uint32_t  getFramebufferWidth    ();
    uint32_t  getFramebufferHeight   ();

    //execution commands
    void      clear                  (float r,float g,float b,float a);
    void      drawTriangles          (uint32_t  nofVertices);

    /// \addtogroup gpu_init 00. proměnné, inicializace / deinicializace grafické karty
    /// @{
    /// \todo zde si můžete vytvořit proměnné grafické karty (buffery, programy, ...)

    // buffer data structures
    struct Buffer {
      BufferID id;
      void *data;
    };
    
    std::vector<Buffer>buffers;
    
    // vertex puller data structures
    struct Vertex_puller_indenxing {
      BufferID id;
      IndexType index_type;
    };

    struct Vertex_puller_head {
      BufferID id;
      uint64_t offset;
      uint64_t stride;
      AttributeType attrib_type;
      bool enabled = false;

    };

    struct Vertex_puller_settings_table {
      VertexPullerID vp_table_id;
      struct Vertex_puller_indenxing vp_index; 
      struct Vertex_puller_head vp_head[maxAttributes];
    };

    std::vector<Vertex_puller_settings_table>vp_set_tables;

    uint32_t current_vp = emptyID;

    // porgram structures
    struct Attributes {
      AttributeType att_type = AttributeType::EMPTY;
    };


    struct Shader_program {
      ProgramID sp_id;
      VertexShader vertex_shader;
      FragmentShader fragment_shader;
      Uniforms uniforms;
      AttributeType attributes[maxAttributes];
    };

    std::vector<Shader_program>shader_programs;

    uint32_t current_sp = emptyID;

    // frame buffer data structures
    struct Frame_buffer {
      uint8_t *color_buffer;
      float *depth_buffer;
    };

    struct Frame_buffer frame_buffer;

    uint32_t W;
    uint32_t H;


    // pipeline functions
    std::vector<std::vector<OutVertex>> clip_space_to_screen_space(std::vector<OutVertex>triangle);
    OutVertex incision(OutVertex vertex1, OutVertex vertex2);
    std::vector<OutVertex> perspective_division(std::vector<OutVertex>triangle);
    std::vector<OutVertex> viewpoint_transformation(std::vector<OutVertex>triangle);
    void rasterization(std::vector<OutVertex>triangle);
    InFragment interpolation(InFragment fragment, std::vector<OutVertex>triangle);
    void per_fragment_operation(InFragment in_fragment, OutFragment out_fragment);
    /// @}
};