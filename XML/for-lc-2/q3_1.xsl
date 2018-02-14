<?xml version="1.0" encoding="ISO-8859-1"?>

<xsl:stylesheet version="2.0" id="q3_1"
                xmlns:xsd="http://www.w3.org/2001/XMLSchema"
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                exclude-result-prefixes="xsd">

  <xsl:output method="text"/>

  <xsl:strip-space elements="*"/>

  <xsl:variable name="eol" select="'&#10;'"/>

  <xsl:template match="sf-1">
    <xsl:apply-templates select="entries"/>
  </xsl:template>

  <xsl:template match="entries">
    <xsl:apply-templates select="book">
      <!-- Question 1 -->
      <!--<xsl:sort select="position()" data-type="number" order="descending"/> -->

      <!-- Question 2 -->
      <!--<xsl:sort select="year" data-type="number" order="descending"/> -->

      <!-- Question 3 -->
      <!-- <xsl:sort select="id(author/personrefs/@to)[1]/last | id(editor/personrefs/@to)[1]/last"/> -->
      <!-- <xsl:sort select="id(author/personrefs/@to)[1]/first | id(editor/personrefs/@to)[1]/first"/> -->

      <!-- Question 4 -->
      <xsl:sort select="title/text()"/> 
    </xsl:apply-templates>
  </xsl:template>

  <xsl:template match="book">

    <xsl:apply-templates select="author | editor"/>
    <xsl:apply-templates select="title"/>
    <xsl:apply-templates select="publisher"/>
    <xsl:apply-templates select="year"/>
    <xsl:apply-templates select="$eol"/>
  </xsl:template>

  <xsl:template match="author | editor">
    <xsl:apply-templates/>
  </xsl:template>

  <xsl:template match="personrefs">
    <xsl:apply-templates select="id(@to)"/>
  </xsl:template>

  <xsl:template match="personname">
    <xsl:value-of select="last"/>
    <xsl:choose>
    <xsl:when test="middle">
      <xsl:value-of select="' (',normalize-space(middle), ''"/>
      <xsl:value-of select="first, ')'"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="' (',first,')'"/>
    </xsl:otherwise>
  </xsl:choose>

    <xsl-if test="position() &lt; last()">, </xsl-if>
  </xsl:template>

  <xsl:template match="title">
    <xsl:value-of
      select="normalize-space(current()),' - '"/>
  </xsl:template>

  <xsl:template match="publisher">
    <xsl:value-of
      select="normalize-space(current()),', '"/>
  </xsl:template>

  <xsl:template match="year">
    <xsl:value-of
      select="normalize-space(current()),'.'"/>
  </xsl:template>



</xsl:stylesheet>
