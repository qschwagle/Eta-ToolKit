#include "gl_image.h"

#include "gl_image_program.h"

#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "helpers.h"

static std::vector<float> rectangle = {
	 0.0f,  1.0f,  0.0, 1.0,
	 1.0f,  0.0f,  1.0, 0.0,
	 0.0f,  0.0f,  0.0, 0.0,

	 0.0f,  1.0f,  0.0, 1.0,
	 1.0f,  1.0f,  1.0, 1.0,
	 1.0f,  0.0f,  1.0, 0.0,
};

etk::renderer::opengl::GLImage::GLImage(std::weak_ptr<GLDrawableContext> context) : GLObject(context)
{	
	auto con = context.lock();
	auto weakProgram = con->GetProgramHolder(etk::renderer::opengl::GLImageProgram::GetId());
	if (weakProgram.expired()) {
		con->SetProgram(etk::renderer::opengl::GLImageProgram::GetId(), std::make_shared<GLImageProgram>(GetContext()));
		weakProgram = con->GetProgramHolder(etk::renderer::opengl::GLImageProgram::GetId());
	}
	auto program = weakProgram.lock()->GetProgram();

	program->Use();

	glGenTextures(1, &mTexture);
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER,mVBO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(0));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * rectangle.size(), rectangle.data(), GL_DYNAMIC_DRAW);
}

etk::renderer::opengl::GLImage::~GLImage()
{
	glDeleteTextures(1, &mTexture);
	glDeleteBuffers(1, &mVBO);
	glDeleteVertexArrays(1, &mVAO);
}

void etk::renderer::opengl::GLImage::Draw(std::weak_ptr<ScreenBox> box)
{
    if (GetContext().expired()) {
        throw std::exception("etk::renderer::opengl::GLFilledRectangle::Draw(): Tried to draw object without context");
        return;
    }
	auto context = GetContext().lock();
	auto p = context->GetProgramHolder(etk::renderer::opengl::GLImageProgram::GetId()).lock();
	auto program = p->GetProgram();

    const glm::vec2& pos = GetPos();

	program->Use();

	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(GetPos().x, -1.0*GetPos().y, 0.0f));
	glm::vec3 my_scale{ mWidth, -1.0f* mHeight, 1.0 };
	model = glm::scale(model, my_scale);

	GLint uniModel = program->GetUniformLoc(std::string("model"));
	GLint uniProjView = p->GetProjId();
	program->SetUniformMat4fv(uniModel, glm::value_ptr(model));
	auto proj = CreateOrtho(box.lock()->GetShift(), context->GetWidth(), context->GetHeight());
	auto lbox = box.lock();
	//glViewport(lbox->GetPosAnchor().x, lbox->GetDimensions().y - lbox->GetPosAnchor().y, lbox->GetDimensions().x - lbox->GetPosAnchor().x, lbox->GetPosAnchor().y);
	program->SetUniformMat4fv(uniProjView, glm::value_ptr(proj));

	GLint uniVec = program->GetUniformLoc(std::string("boundary"));
	const auto& eye = box.lock()->GetShift();
	program->SetUniform4f(uniVec, pos.x-eye.x, -1.0f*pos.y + eye.y, mWidth, mHeight);

	glBindVertexArray(mVAO);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void etk::renderer::opengl::GLImage::LoadImage(unsigned char* data, int width, int height, int channels)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, mTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	switch (channels) {
	case 3:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		break;
	case 4:
	default:
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	mWidth = width;
	mHeight = height;
	mChannels = channels;
	glGenerateMipmap(GL_TEXTURE_2D);
}
