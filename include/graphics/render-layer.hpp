#ifndef RENDER_LAYER_HPP_INCLUDED
#define RENDER_LAYER_HPP_INCLUDED

#include "opengl.hpp"
#include "trillek.hpp"
#include "graphics-base.hpp"
#include <rapidjson/document.h>
#include "texture.hpp"
#include <vector>
#include <memory>

namespace trillek {
namespace graphics {

/**
 * \brief A class to manage a color or depth output from a render pass
 */
class RenderAttachment : public GraphicsBase {
public:
    RenderAttachment();
    ~RenderAttachment();
    RenderAttachment(const RenderAttachment &) = delete;
    RenderAttachment& operator=(const RenderAttachment &) = delete;
    RenderAttachment(RenderAttachment &&that);
    RenderAttachment& operator=(RenderAttachment &&that);

    virtual bool SystemStart(const std::list<Property> &);
    virtual bool SystemReset(const std::list<Property> &);

    /**
     * \brief parse an attachment from json
     * \param[in] const std::string& object_name the name of the node
     * \param[in] rapidjson::Value& node The node to parse.
     * \return false on errors, true for success
     */
    virtual bool Parse(const std::string &object_name, rapidjson::Value& node);

    /**
     * \brief Serialize this attachment to the provided JSON node.
     *
     * \param[in] rapidjson::Document& document The document to serialize to.
     * \return bool False if an error occured in serializing.
     */
    virtual bool Serialize(rapidjson::Document& document);

    void Generate(int width, int height, int samplecount);
    void Destroy();
    void BindTexture();
    void AttachToFBO();

    GLenum GetAttach() const { return attachtarget; }
private:
    GLuint renderbuf;
    bool multisample;
    bool multisample_texture;
    bool clearonuse;
    float clearvalues[4];
    GLenum attachtarget;
    int outputnumber;
    std::string texturename;
    std::shared_ptr<Texture> texture;
};

/**
 * \brief A class to handle rendering a pass to a framebuffer
 */
class RenderLayer : public GraphicsBase {
public:
    RenderLayer();
    virtual ~RenderLayer();

    virtual bool SystemStart(const std::list<Property> &);
    virtual bool SystemReset(const std::list<Property> &);

    /**
     * \brief parse a RenderLayer from json
     * \param[in] const std::string& object_name the name of the node
     * \param[in] rapidjson::Value& node The node to parse.
     * \return false on errors, true for success
     */
    virtual bool Parse(const std::string &object_name, rapidjson::Value& node);

    /**
     * \brief Serialize this RenderLayer to the provided JSON node.
     *
     * \param[in] rapidjson::Document& document The document to serialize to.
     * \return bool False if an error occured in serializing.
     */
    virtual bool Serialize(rapidjson::Document& document);

    void BindToRender() const;
    void UnbindFromAll() const;
    void BindToRead() const;

private:

    GLuint fbo_id;
    std::vector<std::string> attachmentnames;
    std::vector<std::weak_ptr<RenderAttachment>> attachments;
};

} // namespace graphics

namespace reflection {

template <> inline const char* GetTypeName<graphics::RenderAttachment>() { return "attachment"; }
template <> inline const unsigned int GetTypeID<graphics::RenderAttachment>() { return 402; }
template <> inline const char* GetTypeName<graphics::RenderLayer>() { return "render"; }
template <> inline const unsigned int GetTypeID<graphics::RenderLayer>() { return 403; }

} // namespace reflection
} // namespace trillek

#endif
